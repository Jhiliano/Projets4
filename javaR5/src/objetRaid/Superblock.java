package objetRaid;

public class Superblock {
	private int nbBlockUsed;
	private int firstFreeByte;
	static final int sizeofSuperblock = 12;
	static final int SuperblockSize = 4;
	static final int inodeStart = SuperblockSize*Block.size;
	
	private int raidType;
	
	Superblock(int raidType) {
		this.nbBlockUsed = 0;
		this.firstFreeByte = 0;
		this.raidType = raidType;
	}
	
	public void firstFreeByte(Raid raid) {
		int sizeInode = inodeStart + Inode.InodeSize*Raid.inodeTableSize*Block.size;
		int firstByteInode = 0;
		int numberOfFiles = 0;
		int numberOfBlocks = 0;
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(raid.getInodes()[i].getFirstByte() != 0) {
				if(firstByteInode < raid.getInodes()[i].getFirstByte()) {
					firstByteInode = raid.getInodes()[i].getFirstByte();
					sizeInode = raid.getInodes()[i].getNblock()*Block.size;
				}
				numberOfFiles +=1;
				numberOfBlocks += raid.getInodes()[i].getNblock();
			}
		}
		this.firstFreeByte = firstByteInode + sizeInode;
		this.nbBlockUsed = numberOfBlocks;
		raid.setNumberOfFiles(numberOfFiles);
	}
	
	public int read(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeofSuperblock];
		if(Stripe.readChunk(buffer, Superblock.sizeofSuperblock, 0, raid) == 1) return 1;
		this.firstFreeByte = Utilitaire.byte_to_int(buffer,Block.size*2);
		if(firstFreeByte != 0) {
			this.raidType = Utilitaire.byte_to_int(buffer,0);
			this.nbBlockUsed = Utilitaire.byte_to_int(buffer,Block.size);
		}
		else {
			this.firstFreeByte(raid);
		}
		return 0;
	}
	
	public int write(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeofSuperblock];
		Utilitaire.int_to_byte(buffer, this.raidType, 0);
		Utilitaire.int_to_byte(buffer, this.nbBlockUsed, Block.size);
		Utilitaire.int_to_byte(buffer, this.firstFreeByte, Block.size*2);
		if(Stripe.writeChunk(buffer, Superblock.sizeofSuperblock, 0, raid) == 1) return 1;
		return 0;
	}

	public int getNbBlockUsed() {
		return nbBlockUsed;
	}
	
	void setNbBlockUsed(int nbBlockUsed) {
		this.nbBlockUsed = nbBlockUsed;
	}

	public int getFirstFreeByte() {
		return firstFreeByte;
	}
	
	void setFirstFreeByte(int firstFreeByte) {
		this.firstFreeByte = firstFreeByte;
	}

	public int getRaidType() {
		return raidType;
	}
	
	
	
}
