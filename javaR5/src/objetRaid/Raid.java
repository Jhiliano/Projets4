package objetRaid;
import java.io.*;

public class Raid {
	private int numberOfFiles;
	private Superblock superblock;
	private Inode[] inodes = new Inode[inodeTableSize];
	static final int inodeTableSize = 10;
	private enum raidType {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};
	private RandomAccessFile[] disk;
	private int nbDisk;
	
	Raid(int raidType, File[] fichiers, int nbDisk) {
		this.numberOfFiles = 0;
		this.superblock = new Superblock(0,0,raidType);
		this.disk = new RandomAccessFile[nbDisk];
		this.nbDisk = nbDisk;
	}
	
	public RandomAccessFile[] getDisk() {
		return disk;
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
