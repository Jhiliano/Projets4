package objetRaid;

public class Raid {
	private int numberOfFiles;
	private Superblock superblock;
	private Inode[] inodes;
	private enum raidType {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};
	private File[] disk;
	private static int nbDisk;
	
	Raid(int raidType, int nbInode, File[] fichiers, int nbDisk) {
		this.numberOfFiles = 0;
		this.superblock = new Superblock(0,0,raidType);
		this.inodes = new Inode[nbInode];
		this.disk = new File[nbDisk];
		this.nbDisk = nbDisk;
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
	public int getNbDisk() {
		return nbDisk;
	}
	
}
