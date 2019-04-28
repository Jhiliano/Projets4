package javaR5;

public class Stripe {
	private Block[] blocks;
	public Stripe(Block[] blocks, int size) {
		this.blocks = new Block[size];
		for (int i = 0; i < size; i++) {
			this.blocks[i] = blocks[i];
		}
	}
	public Block[] getBlocks() {
		return blocks;
	}
	
}
