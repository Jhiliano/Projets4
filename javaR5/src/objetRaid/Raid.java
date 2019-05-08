package objetRaid;
import java.io.*;
/**
 * Classe de l'objet Raid
 * @author Guillaume Fourcroy
 * @version 1.0
 */
public class Raid {
	/**
	 * Le nombre de fichiers
	 */
	private int numberOfFiles;
	/**
	 * le superblock du raid
	 */
	private Superblock superblock;
	/**
	 * le tableau d'inodes du raid
	 */
	private Inode[] inodes;
	/**
	 * la taille du tableau d'inode
	 */
	public static final int inodeTableSize = 10;
	/**
	 * le type du raid
	 */
	private int raidType;
	/**
	 * les disques du raid qui sont representes sous forme de fichiers
	 */
	private File[] disk;
	/**
	 * le nombre de disque du raid
	 */
	private int nbDisk;
	/**
	 * nombre max de disk (mis a 8 pour set le tableau de fichiers) @see Raid#editerFichier(String)
	 */
	public static final int nbMaxDisk = 8;
	/**
	 * le nom du dernier fichier edite
	 * @see Raid#editerFichier(String)
	 */
	private String fileEdit ="";
	/**
	 * Le constructeur de l'objet Raid
	 * @param raidType le type du raid
	 */
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
	/**
	 * Initialise le raid en fonction d'un dossier (contenant les disques)
	 * @param Nomrepertoire le dossier contenant les disques
	 * @return un entier temoin d'erreur
	 */
	public int initRaid(String Nomrepertoire) {
		if(this.initDisk(Nomrepertoire) != 0) return 1;// les disques n'a pas pu etre initalise
		if(this.superblock.read(this) != 0) return 2;// on ne peux pas lire le superblock
		if(Inode.readInodeTable(this) != 0) return 3;// on ne peux pas lire les inodes
		this.numberOfFiles = Inode.getUnusedInode(this);
		if(numberOfFiles == -1) numberOfFiles = 0;// on initialise le nombre de fichiers
		return 0;
	}
	/**
	 * Eteind le raid (sauvegarde les donnees)
	 * @return un entier temoin d'erreur
	 */
	public int shutDownRaid() {
		if(this.superblock.write(this) != 0) return 1;// le superblock n'a pas pu etre ecrit
		if(Inode.writeInodeTable(this) != 0) return 2;// les inodes n'ont pas pu etre ecrit
		for(int i = 0; i < nbDisk; i++) {
		}
		return 0;
	}
	/**
	 * initialise les disques a partir d'un repertoire donne par @see Raid#initRaid(String)
	 * @param Nomrepertoire le dossier contenant les disques
	 * @return un entier temoin d'erreur
	 */
	private int initDisk(String Nomrepertoire) {
		this.nbDisk = 0;
		File repertoire = new File(Nomrepertoire);
		if(!repertoire.isDirectory()) {// cas ou le repertoire est un fichier
			return 1;
		}
		File[] disk = repertoire.listFiles();
		if(disk == null) return 1;// cas ou il y a un repertoire vide
		for (int i = 0; i<disk.length; i++) {
			if (disk[i].isFile() && this.nbDisk <= nbMaxDisk) {
				this.disk[this.nbDisk] = disk[i];
				this.nbDisk+=1;
			}
		}
		return 0;
	}
	/**
	 * Supprime un fichier du raid 5
	 * @param nomFichier le nom du fichier a supprimer
	 * @return un entier temoin d'erreur
	 */
	public int deleteFile(String nomFichier) {
		if(nomFichier == null || nomFichier.equals("")) return 4;//cas ou le nom du fichier est incorrect
		int idSuppression = Fichier.filexist(nomFichier, this);
		if(idSuppression == -1) return 1;// cas ou le fichier n'existe pas
		Inode.deleteInode(this, idSuppression);
		return 0;
	}
	/**
	 * Importe un fichier sur le raid
	 * @param nomFichier le nom du fichier a importer
	 * @return un entier temoin d'erreur
	 */
	public int loadFileToHost(String nomFichier) {
		if(nomFichier == null || nomFichier.equals("")) return 4;// cas ou le nom du fichier est incorrect
		try {
			RandomAccessFile fileIn = new RandomAccessFile(nomFichier,"r");
			if(fileIn.length() > Fichier.sizeMaxFile) {
				fileIn.close();
				return 5;
			}
			Fichier fileBuffer = new Fichier((int) fileIn.length());
			fileIn.read(fileBuffer.getData(), 0, (int) fileIn.length());
			fileIn.close();
			return fileBuffer.write(nomFichier, this);// return le retour de l'ecriture de l'objet fichier

		} catch (IOException e) {
			return 3;
		}
	}
	/**
	 * Export un fichier du raid
	 * @param nomFichier le nom du fichier a exporter
	 * @return un entier temoin d'erreur
	 */
	public int storeFileToHost(String nomFichier) {
		int err;
		if(nomFichier == null || nomFichier.equals("")) return 4;// cas ou le nom du fichier est incorrect
		Fichier filebuffer = new Fichier(0);
		err = filebuffer.read(nomFichier, this);
		if (err != 0) return err;// si il y a une erreur dans la lecture on la return
		try {
			RandomAccessFile fileOut = new RandomAccessFile(nomFichier,"rw");
			fileOut.write(filebuffer.getData(), 0, filebuffer.getSize());
			fileOut.close();
		} catch (IOException e) {
			return 3;// erreur dans l'ecriture du fichier
		}
		return 0;
	}
	/**
	 * Ajoute un fichier vierge (contnant un caractere : \0)
	 * @param nomFichier le nom du fichier a ajouter
	 * @return un entier temoin d'erreur
	 */
	public int ajouterFichier(String nomFichier) {
		byte[] data = new byte[1];
		data[0] = 0;
        if(nomFichier == null || nomFichier.equals("")) return 3;// cas ou le nom du fichier est incorrect
        Fichier fileBuffer = new Fichier(1,data);
        return fileBuffer.write(nomFichier, this);// return le retour de l'ecriture de l'objet fichier
	}
	/**
	 * Edit un fichier en fonction d'une chaine de caractere
	 * @param buffer la chaine de caractere qu'il faut mettrer dans fichier
	 * @return un entier temoin d'erreur
	 */
	public int editerFichier(String buffer) {
		byte[] data;
		data = buffer.getBytes();
		if(this.fileEdit.equals("")) return 4;// cas ou le nom du fichier est incorrect
		Fichier fileBuffer = new Fichier(data.length, data);
		return fileBuffer.write(this.fileEdit, this);// return le retour de l'ecriture de l'objet fichier
	}
	/**
	 * Creer une chaine de caractere a partir d'un nom de fichier
	 * @param nomFichier le nom du fichier a afficher
	 * @return le string a afficher
	 */
	public String afficherFichier(String nomFichier) {
		int err;
		if(nomFichier.equals("")) return nomFichier;// on renvoie une chaine de caractere vide
		Fichier filebuffer = new Fichier(Fichier.sizeMaxFile);
		err = filebuffer.read(nomFichier, this);
		if(err != 0) {
			return "";// on renvoie une chaine de caractere vide
		}
		this.fileEdit = nomFichier;
		return filebuffer.returnStringFile();
		
	}
	/**
	 * Reinitialise les disques du raid 5
	 * @param size la taille de chaque fichiers
	 * @return un entier temoin d'erreur
	 */
	public int reinitialiser(int size) {
		if(Utilitaire.reinitialiserRaid(this, size) != 0) return 1;// on return en cas d'erreur de reinitialisation
		numberOfFiles = 0;
		superblock = new Superblock(5);
		for(int i = 0; i < inodeTableSize; i++) {
			this.inodes[i] = new Inode();
		}
		
		return 0;
	}
	/**
	 * repare le disque idDisque du raid @see Utilitaire#reparerRaid(Raid, int)
	 * @param idDisque le disque a reparer
	 * @return un entier temoin d'erreur
	 */
	public int reparer(int idDisque) {
		return Utilitaire.reparerRaid(this, idDisque);
	}
	/**
	 * Defragmente le disque
	 * @return un entier temoin d'erreur
	 */
	public int defrag() {
		return Utilitaire.defragRaid(this);
	}
	/**
	 * Getter disk
	 * @return les disques du raid
	 */
	File[] getDisk() {
		return disk;
	}
	/**
	 * Getter numberOfFiles
	 * @return le nombre de fichier du raid
	 */
	public int getNumberOfFiles() {
		return numberOfFiles;
	}
	/**
	 * Getter superblock
	 * @return le superblock du raid
	 */
	Superblock getSuperblock() {
		return superblock;
	}
	/**
	 * Getter inodes
	 * @return les inodes du raid
	 */
	public Inode[] getInodes() {
		return inodes;
	}
	/**
	 * Getter nbDisk
	 * @return le nombre de disques du raid 
	 */
	public int getNbDisk() {
		return nbDisk;
	}
	/**
	 * Donne l'espace restant dans le disque
	 * @return l'espace restant
	 */
	public long getSizeLeft() {
		return this.disk[0].length()*4 - this.superblock.getFirstFreeByte();
	}
	/**
	 * Donne le pourcentage de fragmentation on fonction du disques (donnees en fonction des trous)
	 * @return la pourcentage de fragmentation
	 */
	public int getSizeFragmentation() {
		long nbfragmente = this.superblock.getFirstFreeByte() - (this.superblock.getNbBlockUsed()*4 + (Superblock.inodeStart + Inode.InodeSize*Raid.inodeTableSize*Block.size));
		if(getSizeUsed() == 0) {
			return 0;
		} else {
			return (int) ((nbfragmente*100)/getSizeUsed());
		}
	}
	/**
	 * Donne l'espace utilise dans le raid (sans les inodes et le superblock)
	 * @return l'espace utilise
	 */
	public long getSizeUsed() {
		return this.superblock.getNbBlockUsed()*4;
	}
	/**
	 * Setter numberOfFiles
	 * @param numberOfFiles le nombre de fichiers
	 */
	void setNumberOfFiles(int numberOfFiles) {
		this.numberOfFiles = numberOfFiles;
	}
	/**
	 * Getter RaidType
	 * @return le type du raid
	 */
	public int getRaidType() {
		return raidType;
	}
	/**
	 * Donne le nom de l'inode d'indice id
	 * @param id l'indice de l'inode
	 * @return le nom de l'inode
	 */
	public String getInodeName(int id) {
		return inodes[id].getFilename();
	}
	/**
	 * Donne le statu de l'inode
	 * @param id l'indice de l'inode
	 * @return un boolean temoignant du statu de l'inode
	 */
	public boolean inodeFiled(int id) {
		return inodes[id].getFirstByte() != 0;
	}
}
