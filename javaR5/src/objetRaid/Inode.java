package objetRaid;

import java.io.UnsupportedEncodingException;
/**
 * Classe de l'objet Inode
 * @author Guillaume Fourcroy
 * @version 1.0
 */
	class Inode {
	/**
	 * le nom du fichier de l'inode
	 */
	private String filename;
	/**
	 * la taille du fichier de l'inode
	 */
	private int size;
	/**
	 * le nombre de block du fichier de l'inode
	 */
	private int nblock;
	/**
	 * le premier octet sur lequel est ecrit le fichier dans le raid
	 */
	private int firstByte;
	/**
	 * la taille maximale du nom du nom du fichier de l'inode
	 */
	public static final int fileNameMaxSize = 32;
	/**
	 * la taille de l'inode sans compter la parite, en octet 
	 */
	static final int sizeofinode = 44;
	/**
	 * la taille de l'inode en comptant la parite, en block
	 */
	static final int InodeSize = 16;
	/**
	 * Constructeur de l'inode vide
	 */
	Inode() {
		this.filename = "";
		this.size = 0;
		this.nblock = 0;
		this.firstByte = 0;
	}
	/**
	 * Constructeur de l'inode a remplir 
	 * @param filename le nom du fichier
	 * @param size la taille du fichier
	 * @param pos ma position du premier octet ecrit sur le raid
	 * @param raid le raid ou est contenu le fichier
	 */
	Inode(String filename, int size,int pos, Raid raid) {
		this.filename = filename;
		this.size = size;
		this.nblock = Utilitaire.sizeWithParity(size, raid);
		this.firstByte = pos;
		raid.getSuperblock().firstFreeByte(raid);
	}
	/**
	 * Lis une tablea d'inode dans le raid
	 * @param raid le raid ou il faut lire l'inode
	 * @return un entier temoin d'erreur
	 */
	static int readInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].read(i, raid) == 1) return 1;// les inodes n'ont pas pu etre lues
		}
		return 0;
	}
	/**
	 * Ecrit une tablea d'inode dans le raid
	 * @param raid le raid ou il faut ecrire l'inode
	 * @return un entier temoin d'erreur
	 */
	static int writeInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].write(i,raid) == 1) return 1;// les inodes n'ont pas pu etre ecrites
		}
		return 0;
	}
	/**
	 * Ecrit l'inode dans le raid
	 * @param numero l'indice de l'inode dans le raid
	 * @param raid le raid ou il faut ecrire l'inode
	 * @return un entier temoin d'erreur
	 */
	int write(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.sizeofinode];
		byte[] bufferString = new byte[Inode.fileNameMaxSize];
		try {
			bufferString = this.filename.getBytes("UTF-8");
		} catch (UnsupportedEncodingException e) {
			return 2;// erreur de changement String/Byte
		}
		for(int o = 0; o < Inode.fileNameMaxSize; o++) {
			if (o < bufferString.length)
				buffer[o] = bufferString[o];
			else buffer[o] = (byte) 0;
		}
		Utilitaire.intToByte(buffer, this.size, Inode.fileNameMaxSize + 0);
		Utilitaire.intToByte(buffer, this.nblock,Inode.fileNameMaxSize + Block.size);
		Utilitaire.intToByte(buffer, this.firstByte, Inode.fileNameMaxSize + Block.size*2);
		if(Stripe.writeChunk(buffer, Inode.sizeofinode,Superblock.inodeStart + numero*Inode.InodeSize*Block.size-1, raid) == 1) return 1; // l'inode n'a pas pu etre ecrite
		return 0;
	}
	
	int read(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.sizeofinode];
		int nameLength = 0;
		if(Stripe.readChunk(buffer, Inode.sizeofinode, Superblock.inodeStart + numero*Inode.InodeSize*Block.size-1, raid) == 1) return 1;// l'inode n'a pas pu etre lue
		for(int o = 0; o < Inode.fileNameMaxSize; o++) {
			if(buffer[o] != 0) {
				nameLength++;
			}
		}
		byte[] bufferString = new byte[nameLength];
		for(int o = 0; o < nameLength; o++) {
			bufferString[o] = buffer[o];
		}
		this.filename = new String(bufferString);
		this.size = Utilitaire.byteToInt(buffer,Inode.fileNameMaxSize + 0);
		this.nblock = Utilitaire.byteToInt(buffer,Inode.fileNameMaxSize + Block.size);
		this.firstByte = Utilitaire.byteToInt(buffer,Inode.fileNameMaxSize + Block.size*2);
		return 0;
	}
	/**
	 * Supprime une inode du raid
	 * @param raid le raid ou il faut ecrire le raid
	 * @param pos la position de l'inode a supprimer 
	 */
	static void deleteInode(Raid raid, int pos) {
		int iInode = Inode.getUnusedInode(raid);
		if (iInode == -1) iInode = Raid.inodeTableSize;
		for (int i = pos; i < iInode; i++) {
			raid.getInodes()[i] = raid.getInodes()[i+1];
		}
		raid.getInodes()[iInode-1] = new Inode();
		raid.getSuperblock().firstFreeByte(raid);
	}
	/**
	 * Donne la premiere inode innutilise du raid
	 * @param raid le raid ou il faut chercher
	 * @return l'id de la premier inode innutilise ou -1 si il y en a pas
	 */
	static int getUnusedInode(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if (raid.getInodes()[i].firstByte == 0) return i;
		}
		return -1;
	}
	/**
	 * Getter filename
	 * @return le nom du fichier de l'inode
	 */
	String getFilename() {
		return filename;
	}
	/**
	 * Getter size
	 * @return la taile du fichier de l'inode
	 */
	int getSize() {
		return size;
	}
	/**
	 * Getter nblock
	 * @return le nombre de block utilise de l'inode
	 */
	int getNblock() {
		return nblock;
	}
	/**
	 * Getter firstByte
	 * @return le premier byte du fichier
	 */
	int getFirstByte() {
		return firstByte;
	}
	
}
