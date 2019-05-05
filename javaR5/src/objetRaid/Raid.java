package objetRaid;
import java.io.*;

public class Raid {
	private int numberOfFiles;
	private Superblock superblock;
	private Inode[] inodes;
	static final int inodeTableSize = 10;
	private int raidType;
	private RandomAccessFile[] disk;
	private int nbDisk;
	
	Raid(int raidType, File[] fichiers, int nbDisk) {
		this.numberOfFiles = 0;
		this.superblock = new Superblock(0,0,raidType);
		this.disk = new RandomAccessFile[nbDisk];
		this.nbDisk = nbDisk;
		this.raidType = raidType;
		this.inodes = new Inode[inodeTableSize];
		for(int i = 0; i < inodeTableSize; i++) {
			this.inodes[i] = new Inode();
		}
	}
	
	public int deleteFile(String nomFichier) {
		int idSuppression = File.filexist(nomFichier, this);
		if(idSuppression == -1) return 1;
		Inode.deleteInode(this, idSuppression);
		this.supfile();
		return 0;
	}
	
	public int loadFileToHost(String nomFichier) {
		try {
			RandomAccessFile fileIn = new RandomAccessFile(nomFichier,"r");
			File fileBuffer = new File((int) fileIn.length());
			fileIn.read(fileBuffer.getData(), 0, (int) fileIn.length());
			fileIn.close();
			return fileBuffer.write(nomFichier, this);

		} catch (IOException e) {
			return 3;
		}
	}
	
	public int storeFileToHost(String nomFichier) {
		int err;
		File filebuffer = new File(0);
		err = filebuffer.read(nomFichier, this);
		if (err != 0) return err;
		try {
			RandomAccessFile fileOut = new RandomAccessFile(nomFichier,"w");
			fileOut.write(filebuffer.getData(), 0, filebuffer.getSize());
			fileOut.close();
		} catch (IOException e) {
			return 3;
		}
		return 0;
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
	
	public void addfile() {
		this.numberOfFiles += 1;
	}
	
	public void supfile() {
		this.numberOfFiles -=1;
	}

	void setNumberOfFiles(int numberOfFiles) {
		this.numberOfFiles = numberOfFiles;
	}
	int getRaidType() {
		return raidType;
	}
	
}
