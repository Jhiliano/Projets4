package objetRaid;

import java.util.Base64;

public class Inode {
	private String filename;
	private int size;
	private int nblock;
	private int firstByte;
	public static final int fileNameMaxSize = 32;
	static final int inodeSize = 44;
	
	Inode() {
		this.size = 0;
		this.nblock = 0;
		this.firstByte = 0;
	}

	public static int readInodeTable(Raid raid) {
		byte[] buffer = new byte[Inode.inodeSize];
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(Stripe.readChunk(buffer, Inode.fileNameMaxSize, Superblock.sizeSuperBlock+i*Inode.inodeSize, raid) == 1) return 1;
			Base64.getEncoder().encodeToString(buffer);
			if(Stripe.readChunk(buffer, Inode.fileNameMaxSize - Inode.fileNameMaxSize, Superblock.sizeSuperBlock+i*Inode.inodeSize+Inode.fileNameMaxSize, raid) == 1) return 1;
			
		}
		
	}
	
	public String getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getNblock() {
		return nblock;
	}

	public int getFirstByte() {
		return firstByte;
	}
	
}
