package objetRaid;

import java.io.*;
/**
 * Classe de l'objet Stripe
 * @author Guillaume Fourcroy
 * @version 1.0
 */
class Stripe {
	/**
	 * les block de la stripe
	 */
	private Block[] blocks;
	/**
	 * le nombre de blocks de la stripe
	 */
	private int size;
	/**
	 * Constructeur d'une stripe
	 * @param la taille de la stripe
	 */
	Stripe(int size) {
		this.blocks = new Block[size];
		for(int b = 0; b < size; b++) {
			this.blocks[b] = new Block();
		}
 		this.size = size;
	}
	/**
	 * Calcul le nombre de stripe qu'il faut pour un nombre de blocks donnes
	 * @param nbBlock le nombre de block a calculer
	 * @param size la taille de la stripe
	 * @return le nombre de stripes necessaire
	 */
	static int computeNStripe(int nbBlock, int size) {
		if (nbBlock%(size-1) == 0) return nbBlock/(size-1);
		return nbBlock/(size-1)+1;
	}
	/**
	 * Creer le block de parite
	 * @param pos l'indice du block de parite dans la stripe a creer
	 */
	void computeParity(int pos) {
		this.blocks[pos].blockrepair(this,pos);
	}
	/**
	 * Calcul l'emplacement du block de parite dans la stripe
	 * @param numBande l'indice de la stripe dans le raid
	 * @param raid le raid en fonction duquel il faut effectuer le calcul
	 * @return
	 */
	static int computeParityIndex(int numBande, Raid raid) {
		return (raid.getNbDisk())-((numBande-1)%raid.getNbDisk());
	}
	/**
	 * Lis la stripe a partir de disques du raid
	 * @param pos la position ou il faut ecrire dans le raid
	 * @param disk les disques ou il faut ecrires
	 * @return un entier temoin d'erreur
	 */
	int read(int pos, File[] disk) {
		int erreur = -1;
		for (int d = 0; d < size; d++) {
			if(blocks[d].read(pos, disk[d]) != 0) {
				if(erreur != -1) {
					erreur = d;
				} else {
					return 1;// 2 erreurs de lecture dans la stripe
				}
			}
		}
		if (erreur != -1) {
			this.computeParity(erreur);// reparation si il y a qu'une erreur de lecture
		}
		return 0;
	}
	/**
	 * Ecrit la stripe dans les disques du raid
	 * @param pos la position ou ecrire
	 * @param disk les disques ou ecrire
	 * @return un entier temoin d'erreur
	 */
	int write(int pos, File[] disk) {
		for (int d = 0; d < size; d++) {
			if(blocks[d].write(pos,disk[d]) != 0) return 1;// erreur d'ecriture
		}
		return 0;
	}
	/**
	 * Lit et met dans un buffer une partie du raid
	 * @param buffer le buffer mettre les octets lu
	 * @param size le nombre d'octets a lire
	 * @param pos la position ou lire
	 * @param raid le raid ou il faut lire
	 * @return un entier temoin d'erreur
	 */
	static int readChunk(byte[] buffer, int size, int pos, Raid raid) {
		if(size == 0) return 0;
		int nbBlock = Block.computeNBlock(size);
		int nbStripe = Stripe.computeNStripe(nbBlock, raid.getNbDisk());
		int idParity;
		int decalage = 0;
		for (int s = 0; s < nbStripe; s++) {
			Stripe stripe = new Stripe(raid.getNbDisk());
			idParity = Stripe.computeParityIndex(s+1, raid);
			if (stripe.read(pos, raid.getDisk()) != 0) return 1;// erreur de lecture
			for (int b = 0; b < stripe.getSize(); b++) {
				if (b != idParity-1) {
					for (int o = 0; o < Block.size; o++) {
						if (decalage < size) {
							buffer[decalage] = stripe.getBlocks()[b].getDonnees()[o];
						}
						decalage++;
					}
				}
			}
			pos += Block.size*stripe.getSize();
		}
		return 0;
	}
	/**
	 * Ecrit le contenu du buffer sur le raid
	 * @param buffer le buffer qu'il faut ecrire
	 * @param size le nombre d'octets a ecrire
	 * @param pos la position ou ecrire
	 * @param raid le raid ou il faut ecrire
	 * @return un etier temoin d'erreur
	 */
	static int writeChunk(byte[] buffer, int size, int pos, Raid raid) {
		if(size == 0) return 0;
		int nbBlock = Block.computeNBlock(size);
		int nbStripe = Stripe.computeNStripe(nbBlock, raid.getNbDisk());
		int idParity;
		int decalage = 0;
		for (int s = 0; s < nbStripe; s++) {
			Stripe stripe = new Stripe(raid.getNbDisk());
			idParity = Stripe.computeParityIndex(s+1, raid);
			for (int b = 0; b < stripe.getSize(); b++) {
				if (b != idParity-1) {
					for (int o = 0; o < Block.size; o++) {
						if (decalage < size) {
							stripe.getBlocks()[b].getDonnees()[o] = buffer[decalage];
						} else {
							stripe.getBlocks()[b].getDonnees()[o] = '0';
						}
						decalage++;
					}
				}
			}
			stripe.computeParity(idParity-1);
			if (stripe.write(pos, raid.getDisk()) != 0) return 1;// erreur d'ecriture
			pos += Block.size*stripe.getSize();
		}
		return 0;
	}
	/**
	 * Getter blocks
	 * @return les blocks de la stripe
	 */
	Block[] getBlocks() {
		return blocks;
	}
	/**
	 * Getter size
	 * @return la taille de la stripe
	 */
	int getSize() {
		return size;
	}
}
