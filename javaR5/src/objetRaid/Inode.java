package objetRaid;

import java.io.UnsupportedEncodingException;

public class Inode {
	private String filename;
	private int size;
	private int nblock;
	private int firstByte;
	public static final int fileNameMaxSize = 32;
	static final int sizeofinode = 44;
	static final int InodeSize = 16;
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
		raid.getSuperblock().firstFreeByte(raid);
	}

	public static int readInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].read(i, raid) == 1) return 1;
		}
		return 0;
	}
	
	public static int writeInodeTable(Raid raid) {
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].firstByte != 0) {
				if(raid.getInodes()[i].write(i,raid) == 1) return 1;
			}
		}
		return 0;
	}
	
	private int write(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.sizeofinode];
		byte[] bufferString = new byte[Inode.fileNameMaxSize];
		try {
			bufferString = this.filename.getBytes("UTF-8");
		} catch (UnsupportedEncodingException e) {
			return 2;
		}
		for(int o = 0; o < Inode.fileNameMaxSize; o++) {
			if (o < bufferString.length)
				buffer[o] = bufferString[o];
			else buffer[o] = (byte) 0;
		}
		Utilitaire.int_to_byte(buffer, this.size, Inode.fileNameMaxSize + 0);
		Utilitaire.int_to_byte(buffer, this.nblock,Inode.fileNameMaxSize + Block.size);
		Utilitaire.int_to_byte(buffer, this.firstByte, Inode.fileNameMaxSize + Block.size*2);
		if(Stripe.writeChunk(buffer, Inode.sizeofinode,Superblock.inodeStart + numero*Inode.InodeSize*Block.size-1, raid) == 1) return 1;
		return 0;
	}
	
	private int read(int numero, Raid raid) {
		byte[] buffer = new byte[Inode.sizeofinode];
		int nameLength = 0;
		if(Stripe.readChunk(buffer, Inode.sizeofinode, Superblock.inodeStart + numero*Inode.InodeSize*Block.size-1, raid) == 1) return 1;
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
