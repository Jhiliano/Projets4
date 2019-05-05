package objetRaid;

public class File {
	private int size;
	private byte[] data;
	public static final int sizeMaxFile = 50*1024;
	
	public File(int size, byte[] data) {
		this.data = new byte[sizeMaxFile];
		for(int i = 0; i < size; i++) {
			this.data[i] = data[i];
		}
	}
	
	public File(int size) {
		this.data = new byte[sizeMaxFile];
		this.size = size;
	}
	
	static int filexist(String nomFichier,Raid raid) {
		for(int i = 0; i < Inode.inodeSize; i++) {
			if(nomFichier.equals(raid.getInodes()[i].getFilename())) {
				return i;
			}
		}
		return -1;
	}
	
	public int write(String nomFichier, Raid raid) {
		int idEcriture = File.filexist(nomFichier, raid);
		int firstByte;
		if(idEcriture == -1) {
			idEcriture = Inode.getUnusedInode(raid);
			firstByte = raid.getSuperblock().getFirstFreeByte();
			raid.addfile();
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
		if (Stripe.writeChunk(this.data, this.size, firstByte, raid) != 2) return 2;
		raid.getInodes()[idEcriture] = new Inode(nomFichier,this.size, firstByte, raid);
		return 0;
	}
	
	public int read(String nomFichier, Raid raid) {
		int idLecture = File.filexist(nomFichier, raid);
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
