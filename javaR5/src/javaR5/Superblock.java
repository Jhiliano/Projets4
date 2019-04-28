package javaR5;

public class Superblock {
	private int nbBlockUsed;
	private int firstFreeByte;
	private enum raidType {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};
	Superblock(int nbBlockUsed, int firstFreeByte, int raidType) {
		this.nbBlockUsed = nbBlockUsed;
		this.firstFreeByte = firstFreeByte;
	}
	public int getNbBlockUsed() {
		return nbBlockUsed;
	}
	public int getFirstFreeByte() {
		return firstFreeByte;
	}
	
}
