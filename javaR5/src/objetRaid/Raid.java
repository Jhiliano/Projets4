package objetRaid;
import java.io.*;

public class Raid {
	private int numberOfFiles;
	private Superblock superblock;
	private Inode[] inodes;
	public static final int inodeTableSize = 10;
	private int raidType;
	private File[] disk;
	private int nbDisk;
	public static final int nbMaxDisk = 8;
	private String fileEdit ="";
	
	public Raid(int raidType) {
		this.numberOfFiles = 0;
		this.disk = new File[nbMaxDisk];
		this.raidType = raidType;
		this.superblock = new Superblock(raidType);
		this.inodes = new Inode[inodeTableSize];
		for(int i = 0; i < inodeTableSize; i++) {
			this.inodes[i] = new Inode();
		}
	}
	
	public int initRaid(String Nomrepertoire) {
		if(this.initDisk(Nomrepertoire) != 0) return 1;
		if(this.superblock.read(this) != 0) return 2;
		if(Inode.readInodeTable(this) != 0) return 3;
		this.numberOfFiles = Inode.getUnusedInode(this);
		if(numberOfFiles == -1) numberOfFiles = 0;
		return 0;
	}
	
	public int shutDownRaid() {
		if(this.superblock.write(this) != 0) return 1;
		if(Inode.writeInodeTable(this) != 0) return 2;
		for(int i = 0; i < nbDisk; i++) {
		}
		return 0;
	}
	
	private int initDisk(String Nomrepertoire) {
		this.nbDisk = 0;
		File repertoire = new File(Nomrepertoire);
		if(!repertoire.isDirectory()) {
			return 1;
		}
		File[] disk = repertoire.listFiles();
		if(disk == null) return 1;
		for (int i = 0; i<disk.length; i++) {
			if (disk[i].isFile() && this.nbDisk <= nbMaxDisk) {
				this.disk[this.nbDisk] = disk[i];
				this.nbDisk+=1;
			}
		}
		return 0;
	}
	
	public int deleteFile(String nomFichier) {
		if(nomFichier.equals("")) return 4;
		int idSuppression = Fichier.filexist(nomFichier, this);
		if(idSuppression == -1) return 1;
		Inode.deleteInode(this, idSuppression);
		return 0;
	}
	
	public int loadFileToHost(String nomFichier) {
		if(nomFichier.equals("")) return 4;
		try {
			RandomAccessFile fileIn = new RandomAccessFile(nomFichier,"r");
			Fichier fileBuffer = new Fichier((int) fileIn.length());
			fileIn.read(fileBuffer.getData(), 0, (int) fileIn.length());
			fileIn.close();
			return fileBuffer.write(nomFichier, this);

		} catch (IOException e) {
			return 3;
		}
	}
	
	public int storeFileToHost(String nomFichier) {
		int err;
		if(nomFichier.equals("")) return 4;
		Fichier filebuffer = new Fichier(0);
		err = filebuffer.read(nomFichier, this);
		if (err != 0) return err;
		try {
			RandomAccessFile fileOut = new RandomAccessFile(nomFichier,"rw");
			fileOut.write(filebuffer.getData(), 0, filebuffer.getSize());
			fileOut.close();
		} catch (IOException e) {
			return 3;
		}
		return 0;
	}
	
	public int ajouterFichier(String nomFichier) {
		Fichier fileBuffer = new Fichier(0);
		return fileBuffer.write(nomFichier, this);
	}
	
	public int editerFichier(String buffer) {
		byte[] data = new byte[buffer.length()*2];
		try {
			data = buffer.getBytes("UTF-8");
		} catch (UnsupportedEncodingException e) {
			return 3;
		}
		if(this.fileEdit.equals("")) return 4;
		Fichier fileBuffer = new Fichier(data.length, data);
		return fileBuffer.write(this.fileEdit, this);
	}
	
	public String afficherFichier(String nomFichier) {
		int err;
		if(nomFichier.equals("")) return nomFichier;
		Fichier filebuffer = new Fichier(Fichier.sizeMaxFile);
		err = filebuffer.read(nomFichier, this);
		if(err != 0) {
			return "";
		}
		this.fileEdit = nomFichier;
		return filebuffer.returnStringFile();
		
	}
	
	public File[] getDisk() {
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
	
	void setNumberOfFiles(int numberOfFiles) {
		this.numberOfFiles = numberOfFiles;
	}

	int getRaidType() {
		return raidType;
	}
	
}
