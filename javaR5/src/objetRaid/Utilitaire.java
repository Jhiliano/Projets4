package objetRaid;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
/**
 * Classe Utilitaire du raid
 * @author Guillaume Fourcroy
 * @version 1.0
 */
class Utilitaire {
	/**
	 * Transforme 4 byte dans un tableau de byte en 1 int
	 * @param octet le tableau a lire
	 * @param pos la postion ou lire
	 * @return le int cree
	 */
	static int byteToInt(byte[] octet, int pos) {
	    ByteBuffer byteBuffer = ByteBuffer.wrap(octet, pos, 4);
	    return byteBuffer.getInt();
	}
	/**
	 * Transforme 1 int en 4 byte dans un tableau
	 * @param octet le tableau ou ecrire l'int
	 * @param nombre l'int a ecrire
	 * @param pos la position ou ecrire
	 */
	static void intToByte(byte[] octet, int nombre, int pos) {
		for(int b = 0; b < 4; b += 1) {
			octet[pos+b] = (byte) ((nombre >> (8*(3-b))) & 0xff); // on prend d'abord les 8*sizeof(uint) bits a gauche et ensuite les suivant ect..
		}
	}
	/**
	 * Calcul en fonction  d'un nombre d'octets donne le nombre d'octets dans le raid avec parite
	 * @param size le nombre d'octet a calculer
	 * @param raid le raid de reference pour le calcul
	 * @return les octets necessaire avec parite
	 */
	static int sizeWithParity(int size, Raid raid) {
		return Stripe.computeNStripe(Block.computeNBlock(size), raid.getNbDisk())*Block.size;
	}
	/**
	 * Defragmenter un raid
	 * @param raid le raid a defragmenter
	 * @return un entier temoin d'erreur
	 */
	static int defragRaid(Raid raid) {
		Fichier file;
		int pos = Superblock.inodeStart + Inode.InodeSize*Raid.inodeTableSize*Block.size;
		for(int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].getFirstByte() != 0) {
				file = new Fichier(raid.getInodes()[i].getSize());
				if(file.move(pos, raid.getInodes()[i], raid) != 0) return 1;// erreur de lecture ou d'ecriture
				raid.getInodes()[i] = new Inode(raid.getInodes()[i].getFilename(),raid.getInodes()[i].getSize(),pos,raid);
				pos+= raid.getInodes()[i].getNblock()*Block.size;
			}
		}
		
		return 0;
	}
	/**
	 * reinitialise les disques d'un raid
	 * @param raid le raid a reinitialiser
	 * @param size la taille des disques a creer
	 * @return un entier temoin d'erreur
	 */
	static int reinitialiserRaid(Raid raid, int size) {
		for (int d = 0; d<raid.getNbDisk(); d++) {
			try {
				raid.getDisk()[d].delete();
				RandomAccessFile file = new RandomAccessFile(raid.getDisk()[d],"rw");
				for(int o = 0; o < size; o++) {
						file.seek(o);
						file.writeByte(0);
				}
				file.close();
				} catch (IOException e) {
					return 1;// erreur d'ecriture dans les fichier
				}
		}
		return 0;
	}
	/**
	 * Repare un disque d'un raid 
	 * @param raid le raid a reparer
	 * @param idDisque le disque a reparer
	 * @return un entier temoin d'erreur
	 */
	static int reparerRaid(Raid raid, int idDisque) {
		int nbStripe = raid.getSuperblock().getNbBlockUsed() + Superblock.SuperblockSize + Inode.InodeSize;
		for (int s = 0; s < nbStripe; s++) {
			Stripe stripe = new Stripe(raid.getNbDisk());
			if(stripe.read(stripe.getSize()*Block.size*s, raid.getDisk()) != 0) return 1;
			stripe.getBlocks()[idDisque].blockrepair(stripe, idDisque);
			if(stripe.write(stripe.getSize()*Block.size*s, raid.getDisk()) != 0) return 1;
		}
		return 0;
	}
}
