package objetRaid;

import java.io.*;

public class Stripe {
	private Block[] blocks;
	private int size;
	public Stripe(int size) {
		this.blocks = new Block[size];
		for(int b = 0; b < size; b++) {
			this.blocks[b] = new Block();
		}
 		this.size = size;
	}
	
	public static int computeNStripe(int nbBlock, int size) {
		if (nbBlock%(size-1) == 0) return nbBlock/(size-1);
		return nbBlock/(size-1)+1;
	}
	
	public void computeParity(int pos) {
		this.blocks[pos].blockrepair(this,pos);
	}
	
	public static int computeParityIndex(int numBande, Raid raid) {
		return (raid.getNbDisk())-((numBande-1)%raid.getNbDisk());
	}
	
	public int read(int pos, File[] disk) {
		int erreur = -1;
		for (int d = 0; d < size; d++) {
			if(blocks[d].read(pos, disk[d]) != 0) {
				if(erreur != -1) {
					erreur = d;
				} else {
					return 1;
				}
			}
		}
		if (erreur != -1) {
			this.computeParity(erreur);
		}
		return 0;
	}
	
	public int write(int pos, File[] disk) {
		for (int d = 0; d < size; d++) {
			if(blocks[d].write(pos,disk[d]) != 0) return 1;
		}
		return 0;
	}
	
	public static int readChunk(byte[] buffer, int size, int pos, Raid raid) {
		if(size == 0) return 0;
		int nbBlock = Block.computeNBlock(size);
		int nbStripe = Stripe.computeNStripe(nbBlock, raid.getNbDisk());
		int idParity;
		int decalage = 0;
		for (int s = 0; s < nbStripe; s++) {
			Stripe stripe = new Stripe(raid.getNbDisk());
			idParity = Stripe.computeParityIndex(s+1, raid);
			if (stripe.read(pos, raid.getDisk()) != 0) return 1;
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
	
	public static int writeChunk(byte[] buffer, int size, int pos, Raid raid) {
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
			if (stripe.write(pos, raid.getDisk()) != 0) return 1;
			pos += Block.size*stripe.getSize();
		}
		return 0;
	}
	
	public Block[] getBlocks() {
		return blocks;
	}

	public int getSize() {
		return size;
	}
}
