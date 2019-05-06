package objetRaid;

public class Fichier {
	private int size;
	private byte[] data;
	public static final int sizeMaxFile = 50*1024;
	
	public Fichier(int size, byte[] data) {
		this.data = new byte[sizeMaxFile];
		for(int i = 0; i < size; i++) {
			this.data[i] = data[i];
		}
	}
	
	public Fichier(int size) {
		this.data = new byte[sizeMaxFile];
		this.size = size;
	}
	
	static int filexist(String nomFichier,Raid raid) {
		for(int i = 0; i < Raid.inodeTableSize; i++) {
			if(nomFichier.equals(raid.getInodes()[i].getFilename())) {
				return i;
			}
		}
		return -1;
	}
	
	public String returnStringFile() {
		byte[] buffer = new byte[this.size];
		for (int i = 0; i < this.size; i++) {
			buffer[i] = this.data[i];
		}
		return new String(buffer);
	}
	
	public int write(String nomFichier, Raid raid) {
		int idEcriture = Fichier.filexist(nomFichier, raid);
		int firstByte;
		if(idEcriture == -1) {
			idEcriture = Inode.getUnusedInode(raid);
			firstByte = raid.getSuperblock().getFirstFreeByte();
		}
		else {
			if (size <= raid.getInodes()[idEcriture].getSize()) {
				firstByte = raid.getInodes()[idEcriture].getFirstByte();
			}
			else {
				Inode.deleteInode(raid, idEcriture);
				idEcriture = Inode.getUnusedInode(raid);
				firstByte = raid.getSuperblock().getFirstFreeByte();
			}
			
		}
		if (idEcriture == -1) return 1;
		if (this.size != 0) {
			if (Stripe.writeChunk(this.data, this.size, firstByte, raid) != 0) return 2;
		}
		raid.getInodes()[idEcriture] = new Inode(nomFichier,this.size, firstByte, raid);
		raid.getSuperblock().firstFreeByte(raid);
		return 0;
	}
	
	public int read(String nomFichier, Raid raid) {
		int idLecture = Fichier.filexist(nomFichier, raid);
		if(idLecture == -1) return 1;
		this.size = raid.getInodes()[idLecture].getSize();
		if (Stripe.readChunk(this.data, this.size, raid.getInodes()[idLecture].getFirstByte(), raid) != 0) return 2;
		return 0;
	}
	
	public int getSize() {
		return size;
	}

	public byte[] getData() {
		return data;
	}
	
	
}