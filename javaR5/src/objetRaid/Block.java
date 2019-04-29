package objetRaid;
import java.io.*;

public class Block {
	private char[] donnees;
	public static final int size = 4;
	public Block() {
		this.donnees = new char[size];
	}
	
	public static int computeNBlock(int nblock) {
		if(nblock%size == 0) return nblock/size;
		return nblock/size+1;
	}
	
	public void blockrepair(Block[] blocks, int nbBlock) {
		for (int d = 0; d < Block.size; d++) {
			donnees[d] = 0;
		}
		for (int b = 0; b < nbBlock; b++) {
			for (int d = 0; d < Block.size; d++) {
				donnees[d] ^= blocks[b].getDonnees()[d];
			}
		}
	}
	
	public int write(int pos, RandomAccessFile fichier) {
		for(int c = 0; c < size; c++) {
			try {
				fichier.seek(pos+c);
				fichier.writeChar(donnees[c]);
			} catch (IOException e) {
				return 1;
			}
		}
		return 0;
	}
	
	public int read(int pos, RandomAccessFile fichier) {
		for(int c = 0; c < size; c++) {
			try {
				fichier.seek(pos+c);
				fichier.readChar();
			} catch (IOException e) {
				return 1;
			}
		}
		return 0;
	}
	
	public void printblock() {
		for(int i = 0; i < size; i++) {
			System.out.print(String.format("%02x",donnees[i]));			
		}
	}
	
	public char[] getDonnees() {
		return donnees;
	}
}
