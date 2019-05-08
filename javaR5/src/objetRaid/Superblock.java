package objetRaid;
/**
 * Classe de l'objet Superblock
 * @author Guillaume Fourcroy
 * @version 1.0
 */
	class Superblock {
	/**
	 * le nombre de block utilise du raid 
	 */
	private int nbBlockUsed;
	/**
	 * le premier entier libre
	 */
	private int firstFreeByte;
	/**
	 * la taille du superblock sans parite, en octets
	 */
	static final int sizeofSuperblock = 12;
	/**
	 * la taille du superblock avec parite, en block
	 */
	static final int SuperblockSize = 4;
	/**
	 * la position de demarage des inodes
	 */
	static final int inodeStart = SuperblockSize*Block.size;
	/**
	 * le type du raid
	 */
	private int raidType;
	/**
	 * Constructeur du superblock
	 * @param raidType le type du raid
	 */
	Superblock(int raidType) {
		this.nbBlockUsed = 0;
		this.firstFreeByte = inodeStart + Inode.InodeSize*Raid.inodeTableSize*Block.size;
		this.raidType = raidType;
	}
	/**
	 * met a jour le superblock en fonction du raid
	 * @param raid le raid de reference
	 */
	void firstFreeByte(Raid raid) {
		int sizeInode = inodeStart + Inode.InodeSize*Raid.inodeTableSize*Block.size;
		int firstByteInode = 0;
		int numberOfFiles = 0;
		int numberOfBlocks = 0;
		for (int i = 0; i < Raid.inodeTableSize; i++) {// parcours des inodes
			if(raid.getInodes()[i].getFirstByte() != 0) {
				if(firstByteInode < raid.getInodes()[i].getFirstByte()) {
					firstByteInode = raid.getInodes()[i].getFirstByte();
					sizeInode = raid.getInodes()[i].getNblock()*Block.size;
				}
				numberOfFiles +=1;
				numberOfBlocks += raid.getInodes()[i].getNblock();
			}
		}
		this.firstFreeByte = firstByteInode + sizeInode;// maj du Superblock
		this.nbBlockUsed = numberOfBlocks;
		raid.setNumberOfFiles(numberOfFiles);// maj du raid
	}
	/**
	 * Lis le superblock dans les disques
	 * @param raid le raid dans lequel il faut lire
	 * @return un temoin d'erreur
	 */
	int read(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeofSuperblock];
		if(Stripe.readChunk(buffer, Superblock.sizeofSuperblock, 0, raid) == 1) return 1;// erreur de lecture
		this.firstFreeByte = Utilitaire.byteToInt(buffer,Block.size*2);
		if(firstFreeByte != 0) {// cas d'un raid non vide
			this.raidType = Utilitaire.byteToInt(buffer,0);
			this.nbBlockUsed = Utilitaire.byteToInt(buffer,Block.size);
		}
		else {
			this.firstFreeByte(raid);// raid vide
		}
		return 0;
	}
	/**
	 * Ecris le superblock dans les disques
	 * @param raid le raid dans lequel il faut ecrire
	 * @return un temoin d'erreur
	 */
	int write(Raid raid) {
		byte[] buffer = new byte[Superblock.sizeofSuperblock];
		Utilitaire.intToByte(buffer, this.raidType, 0);
		Utilitaire.intToByte(buffer, this.nbBlockUsed, Block.size);
		Utilitaire.intToByte(buffer, this.firstFreeByte, Block.size*2);
		if(Stripe.writeChunk(buffer, Superblock.sizeofSuperblock, 0, raid) == 1) return 1;// erreur d'ecriture
		return 0;
	}
	/**
	 * Verifie si le raid est assez grand pour entrer dans le raid
	 * @param size la taille du fichier
	 * @param raid le raid qui va accueillir le fichier
	 * @return un bool temoin de la capacite du raid a accueillir le fichier
	 */
	boolean verifierTailleFichier(int size, Raid raid) {
		return ((firstFreeByte + Utilitaire.sizeWithParity(size,raid)) < raid.getDisk()[0].length()*4);
	}
	/**
	 * Getter nbBlockUsed
	 * @return renvoie le nombre de block utilise du raid
	 */
	int getNbBlockUsed() {
		return nbBlockUsed;
	}
	/**
	 * Setter nBlockUsed
	 * @param nbBlockUsed le nombre de block utilise a changer
	 */
	void setNbBlockUsed(int nbBlockUsed) {
		this.nbBlockUsed = nbBlockUsed;
	}
	/**
	 * Getter firstfreeByte
	 * @return le premier libre
	 */
	public int getFirstFreeByte() {
		return firstFreeByte;
	}
	/**
	 * Setter firstFreeByte
	 * @param firstFreeByte le premier byte utiliser a changer
	 */
	void setFirstFreeByte(int firstFreeByte) {
		this.firstFreeByte = firstFreeByte;
	}
	/**
	 * Getter raidType
	 * @return le type de raid
	 */
	int getRaidType() {
		return raidType;
	}
	
	
	
}
