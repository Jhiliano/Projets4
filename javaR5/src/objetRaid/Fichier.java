package objetRaid;
/**
 * Classe de l'objet Fichier
 * @author Guillaume Fourcroy
 * @version 1.0
 */
	class Fichier {
	/**
	 * la taille des donnees du fichier
	 */
	private int size;
	/**
	 * les donnees du fichier
	 */
	private byte[] data;
	/**
	 * la taille maximum d'un fichier
	 */
	public static final int sizeMaxFile = 50*1024;
	/**
	 * Constructeur de l'objet fichier
	 * @param size la taille du fichier
	 * @param data les donnees du fichier
	 */
	Fichier(int size, byte[] data) {
		this.data = new byte[sizeMaxFile];
		for(int i = 0; i < size; i++) {
			this.data[i] = data[i];
		}
		this.size = size;
	}
	/**
	 * Constructeur de l'objet fichier
	 * @param size la taille du fichier
	 */
	Fichier(int size) {
		this.data = new byte[sizeMaxFile];
		this.size = size;
	}
	/**
	 * Verifie si le fichier est dans le raid
	 * @param nomFichier le nom du fichier a verifier
	 * @param raid le raid dans lequel verifier
	 * @return -1 si il existe pas, sinon l'id de l'inode
	 */
	static int filexist(String nomFichier,Raid raid) {
		for(int i = 0; i < Raid.inodeTableSize; i++) {
			if(nomFichier.equals(raid.getInodes()[i].getFilename())) {
				return i;
			}
		}
		return -1;
	}
	/**
	 * Transforme les donnees d'un fichier en string @see Raid#afficherFichier(String)
	 * @return les donnes en string
	 */
	String returnStringFile() {
		String s; 
		byte[] buffer = new byte[this.size];
		for (int i = 0; i < this.size; i++) {
			buffer[i] = this.data[i];
		}
		s = new String(buffer);
		return s;
	}
	/**
	 * Ecrit le fichier dans un raid
	 * @param nomFichier le nom du fichier
	 * @param raid le raid dans lequel ecrire
	 * @return un entier indicateur d'erreur
	 */
	int write(String nomFichier, Raid raid) {
		int idEcriture = Fichier.filexist(nomFichier, raid);
		int firstByte;
		if(idEcriture == -1) {
			if(!raid.getSuperblock().verifierTailleFichier(size, raid)) return 3;//si le raid est plein
			idEcriture = Inode.getUnusedInode(raid);
			firstByte = raid.getSuperblock().getFirstFreeByte();
		}
		else {
			if (size <= raid.getInodes()[idEcriture].getSize()) {
				firstByte = raid.getInodes()[idEcriture].getFirstByte();
			}
			else {
				if(!raid.getSuperblock().verifierTailleFichier(size, raid)) return 3;// si le raid est plein
				Inode.deleteInode(raid, idEcriture);
				idEcriture = Inode.getUnusedInode(raid);
				firstByte = raid.getSuperblock().getFirstFreeByte();
			}
			
		}
		if (idEcriture == -1) return 1;//plus d'inodes disponibles
		if (this.size != 0) {
			if (Stripe.writeChunk(this.data, this.size, firstByte, raid) != 0) return 2;// erreur d'ecriture
		}
		raid.getInodes()[idEcriture] = new Inode(nomFichier,this.size, firstByte, raid);
		raid.getSuperblock().firstFreeByte(raid);
		return 0;
	}
	/**
	 * Lis le fichier dans un raid
	 * @param nomFichier le nom du fichier
	 * @param raid le raid dans lequel ecrire
	 * @return un entier temoin d'erreur
	 */
	int read(String nomFichier, Raid raid) {
		int idLecture = Fichier.filexist(nomFichier, raid);
		if(idLecture == -1) return 1;// le fichier n'existe pas
		this.size = raid.getInodes()[idLecture].getSize();
		if (Stripe.readChunk(this.data, this.size, raid.getInodes()[idLecture].getFirstByte(), raid) != 0) return 2;// erreur de lecture
		return 0;
	}
	/**
	 * Deplace les donnees d'une inode voir {@link Utilitaire#defragRaid(Raid)}
	 * @param pos la position ou ecrire
	 * @param inode l'inode a ecrire
	 * @param raid le raid dans lequel ecrire
	 * @return un entier temoin d'erreur
	 */
	int move(int pos, Inode inode, Raid raid) {
		if(Stripe.readChunk(this.data, inode.getSize(), inode.getFirstByte(), raid) != 0) return 1;// erreur de lecture
		if(Stripe.writeChunk(this.data, inode.getSize(), pos, raid) != 0) return 2;// erreur d'ecriture
		return 0;
	}
	/**
	 * Getter Size
	 * @return la taille du fichier
	 */
	int getSize() {
		return size;
	}
	/**
	 * Getter Data
	 * @return les donnees du fichier
	 */
	byte[] getData() {
		return data;
	}
	
	
}