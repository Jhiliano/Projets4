package objetRaid;
import java.io.*;

public class Block {
	private byte[] donnees;
	public static final int size = 4;
	public Block() {
		this.donnees = new byte[size];
	}
	
	public static int computeNBlock(int nblock) {
		if(nblock%size == 0) return nblock/size;
		return nblock/size+1;
	}
	
	public void blockrepair(Stripe stripe, int pos) {
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
	
	public int write(int pos, File disk) {
		try {
		RandomAccessFile file = new RandomAccessFile(disk,"rw");
		for(int o = 0; o < size; o++) {
				file.seek(pos+o);
				file.writeByte(donnees[o]);
		}
		file.close();
		} catch (IOException e) {
			return 1;
		}
		return 0;
	}
	
	public int read(int pos, File disk) {
		try {
		RandomAccessFile file = new RandomAccessFile(disk,"rw");
		for(int o = 0; o < size; o++) {
				file.seek(pos+o);
				donnees[o] = file.readByte();
		}
		file.close();
		} catch (IOException e) {
			return 1;
		}
		return 0;
	}
	
	public void printblock() {
		for(int i = 0; i < size; i++) {
			System.out.print(String.format("%02x ",donnees[i]));			
		}
	}
	
	public byte[] getDonnees() {
		return donnees;
	}
}
