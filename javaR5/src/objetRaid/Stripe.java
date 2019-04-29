package objetRaid;

import java.io.RandomAccessFile;

public class Stripe {
	private Block[] blocks;
	private int size;
	public Stripe(Block[] blocks, int size) {
		this.blocks = new Block[size];
		for (int i = 0; i < size; i++) {
			this.blocks[i] = blocks[i];
		}
		this.size = size;
	}
	
	public static int computeNStripe(int nbBlock, int size) {
		if (nbBlock%(size-1) == 0) return nbBlock/(size-1);
		return nbBlock/(size-1)+1;
	}
	
	public void computeParity(int pos) {
		Block[] blocks = new Block[size-1];
		int i = 0;
		int b = 0;
		while (b < size) {
			if (b != pos) {
				blocks[i] = this.blocks[b];
				i++;
			}
			b++;
		}
		this.blocks[pos].blockrepair(blocks, size-1);
	}
	
	public static int computeParityIndex(int numBande, Raid raid) {
		return (raid.getNbDisk())-((numBande-1)%raid.getNbDisk());
	}
	
	public int read(int pos, Raid raid, RandomAccessFile[] fichiers) {
		int erreur = -1;
		for (int i = 0; i < size; i++) {
			if(blocks[i].read(pos, fichiers[i]) == 1) {
				if(erreur != -1) {
					erreur = i;
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
	
	public int write(int pos, Raid raid, RandomAccessFile[] fichiers) {
		for (int i = 0; i < size; i++) {
			if(blocks[i].write(pos,fichiers[i]) == 1) return 1;
		}
		return 0;
	}
	
	public Block[] getBlocks() {
		return blocks;
	}
}
