package objetRaid;

public class Block {
	private char[] donnees;
	public Block(char[] donnees, int size) {
		this.donnees = new char[size];
		for (int i = 0; i < size; i++) {
			this.donnees[i] = donnees[i];
		}
	}
	public char[] getDonnees() {
		return donnees;
	}
	
}
