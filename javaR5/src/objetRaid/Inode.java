package objetRaid;

public class Inode {
	private char[] filename;
	private int size;
	private int nblock;
	private int firstByte;
	
	Inode(char[] filename,int nameSize, int size, int nblock, int firstByte) {
		filename = new char[nameSize];
		for (int i = 0; i < nameSize; i++) {
			this.filename[i] = filename[i];
		}
		this.size = size;
		this.nblock = nblock;
		this.firstByte = firstByte;
	}

	public char[] getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getNblock() {
		return nblock;
	}

	public int getFirstByte() {
		return firstByte;
	}
	
}
