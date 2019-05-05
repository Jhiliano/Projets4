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
	
	Inode(String filename, int size,int pos, Raid raid) {
		this.filename = filename;
		this.size = size;
		this.nblock = Utilitaire.sizeWithParity(size, raid);
		this.firstByte = pos;
		raid.getSuperblock().setNbBlockUsed(raid.getSuperblock().getNbBlockUsed()+this.nblock);
		raid.getSuperblock().firstFreeByte(raid);
	}

	public static int readInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].write(i, raid) == 1) return 1;
		}
		return 0;
	}
	
	public static int writeInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].read(i,raid) == 1) return 1;
		}
		return 0;
	}
	
	private int read(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.inodeSize];
		byte[] bufferString = new byte[Inode.fileNameMaxSize];
		bufferString = this.filename.getBytes();
		for(int o = 0; o < Inode.fileNameMaxSize; o++) {
			buffer[o] = bufferString[o];
		}
		Utilitaire.int_to_byte(buffer, Inode.fileNameMaxSize + 0, this.size);
		Utilitaire.int_to_byte(buffer, Inode.fileNameMaxSize + Block.size, this.nblock);
		Utilitaire.int_to_byte(buffer, Inode.fileNameMaxSize + Block.size*2, this.firstByte);
		if(Stripe.writeChunk(buffer, Inode.inodeSize, Superblock.sizeSuperBlock+numero*Inode.inodeSize, raid) == 1) return 1;
		return 0;
	}
	
	private int write(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.inodeSize];
		byte[] bufferString = new byte[Inode.fileNameMaxSize];
		if(Stripe.readChunk(buffer, Inode.inodeSize, Superblock.sizeSuperBlock+numero*Inode.inodeSize, raid) == 1) return 1;
		for(int o = 0; o < Inode.fileNameMaxSize; o++) {
			bufferString[o] = buffer[o];
		}
		this.filename = Base64.getEncoder().encodeToString(bufferString);
		this.size = Utilitaire.byte_to_int(buffer,Inode.fileNameMaxSize + 0);
		this.nblock = Utilitaire.byte_to_int(buffer,Inode.fileNameMaxSize + Block.size);
		this.firstByte = Utilitaire.byte_to_int(buffer,Inode.fileNameMaxSize + Block.size*2);
		return 0;
	}
	
	public static void deleteInode(Raid raid, int pos) {
		int iInode = Inode.getUnusedInode(raid);
		if (iInode == -1) {
			iInode = Raid.inodeTableSize;
		}
		raid.getSuperblock().setFirstFreeByte(raid.getInodes()[pos].nblock);
		for (int i = pos; i < iInode; i++) {
			raid.getInodes()[i] = raid.getInodes()[i+1];
		}
		raid.getInodes()[iInode-1].firstByte = 0;
		raid.getSuperblock().firstFreeByte(raid);
		raid.supfile();
	}
	
	public static int getUnusedInode(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if (raid.getInodes()[i].firstByte == 0) return i;
		}
		return 0;
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
