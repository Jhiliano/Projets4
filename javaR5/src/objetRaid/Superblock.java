package objetRaid;

public class Superblock {
	private int nbBlockUsed;
	private int firstFreeByte;
	static final int sizeSuperBlock = 12;
	private int raidType;
	
	Superblock(int nbBlockUsed, int firstFreeByte, int raidType) {
		this.nbBlockUsed = nbBlockUsed;
		this.firstFreeByte = firstFreeByte;
		this.raidType = raidType;
	}
	
	public void firstFreeByte(Raid raid) {
		int sizeInode = Utilitaire.sizeWithParity(Superblock.sizeSuperBlock, raid) + Utilitaire.sizeWithParity(Inode.inodeSize, raid)*Raid.inodeTableSize;
		int firstByteInode = 0;
		for (int i = 0; i < Raid.inodeTableSize; i++) {
			if(firstByteInode < raid.getInodes()[i].getFirstByte()) {
				firstByteInode = raid.getInodes()[i].getFirstByte();
				sizeInode = raid.getInodes()[i].getNblock()*Block.size;
			}
		}
		this.firstFreeByte = firstByteInode + sizeInode;
	}
	
	public int write(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeSuperBlock];
		if(Stripe.readChunk(buffer, Superblock.sizeSuperBlock, 0, raid) == 1) return 1;
		this.nbBlockUsed = Utilitaire.byte_to_int(buffer,0);
		this.firstFreeByte = Utilitaire.byte_to_int(buffer,Block.size);
		this.raidType = Utilitaire.byte_to_int(buffer,Block.size*2);
		return 0;
	}
	
	public int read(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeSuperBlock];
		Utilitaire.int_to_byte(buffer, 0, this.nbBlockUsed);
		Utilitaire.int_to_byte(buffer, Block.size, this.firstFreeByte);
		Utilitaire.int_to_byte(buffer, Block.size*2, this.raidType);
		if(Stripe.writeChunk(buffer, Superblock.sizeSuperBlock, 0, raid) == 1) return 1;
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
	
	
	
}
