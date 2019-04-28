package javaR5;

public class Raid {
	private int numberOfFiles;
	private Superblock superblock;
	private Inode[] inodes;
	private enum raidType {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};
	private File[] fichiers;
	Raid(int raidType, int nbInode, File[] fichiers, int nbFichiers) {
		this.numberOfFiles = 0;
		this.superblock = new Superblock(0,0,raidType);
		this.inodes = new Inode[nbInode];
		this.fichiers = new File[nbFichiers];
	}
	public int getNumberOfFiles() {
		return numberOfFiles;
	}
	public Superblock getSuperblock() {
		return superblock;
	}
	public Inode[] getInodes() {
		return inodes;
	}
}
