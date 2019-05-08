package objetRaid;
import java.io.*;
/**
 * Classe de l'objet Block
 * @author Guillaume Fourcroy
 * @version 1.0
 */
class Block {
	/**
	 * les octets du block
	 */
	private byte[] donnees;
	/**
	 * la taille d'un block
	 */
	public static final int size = 4;
	/**
	 * Constructeur de l'objet block
	 */
	Block() {
		this.donnees = new byte[size];
	}
	/**
	 * Calcul le nombre de block necessaire pour un nombre d'octets donnes
	 * @param nboctets le nombre d'octets a calculer
	 * @return le nombre de blocks calcule
	 */
	static int computeNBlock(int nboctets) {
		if( nboctets%size == 0) return  nboctets/size;
		return  nboctets/size+1;
	}
	/**
	 * Repare le block en fonction d'une stripe
	 * @param stripe la stripe du block
	 * @param pos la position du block dans la stripe
	 */
	void blockrepair(Stripe stripe, int pos) {
		for (int d = 0; d < Block.size; d++) {
			donnees[d] = 0;
		}
		for (int b = 0; b < stripe.getSize(); b++) {
			if(b != pos) {
				for (int d = 0; d < Block.size; d++) {
					donnees[d] = (byte) (donnees[d]^stripe.getBlocks()[b].getDonnees()[d]);					
				}
			}
		}
	}
	/**
	 * Ecrit un block sur le raid
	 * @param pos la position ou ecrire le block sur le raid
	 * @param disk le disque ou ecrire le block
	 * @return un entier temoin d'erreur
	 */
	int write(int pos, File disk) {
		try {
		RandomAccessFile file = new RandomAccessFile(disk,"rw");
		for(int o = 0; o < size; o++) {
				file.seek(pos+o);
				file.writeByte(donnees[o]);
		}
		file.close();
		} catch (IOException e) {
			return 1;// probleme d'ecriture dans le fichier
		}
		return 0;
	}
	/**
	 * Lit un block sur le raid 
	 * @param pos la position ou lire le block
	 * @param disk le disque ou lire le block
	 * @return un entier temoin d'erreur
	 */
	int read(int pos, File disk) {
		try {
		RandomAccessFile file = new RandomAccessFile(disk,"rw");
		for(int o = 0; o < size; o++) {
				file.seek(pos+o);
				donnees[o] = file.readByte();
		}
		file.close();
		} catch (IOException e) {
			return 1;// probleme de lecture dans le fichier
		}
		return 0;
	}
	/**
	 * fonction qui affiche un block
	 */
	void printblock() {
		for(int i = 0; i < size; i++) {
			System.out.print(String.format("%02x ",donnees[i]));			
		}
	}
	/**
	 * Getter donnees
	 * @return les octets du block
	 */
	byte[] getDonnees() {
		return donnees;
	}
}
