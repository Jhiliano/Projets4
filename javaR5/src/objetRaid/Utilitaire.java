package objetRaid;

public class Utilitaire {
	public static int byte_to_int(byte[] octet, int pos) {
		return octet[pos]<<24 | octet[pos+1]<<16 | octet[pos+2]<<8 | octet[pos+3];
	}
	
	public static void int_to_byte(byte[] octet, int nombre, int pos) {
		for(int i = 0; i < 4; i += 1) {
			octet[pos+i] = (byte) (nombre>>8*4*(4-i+1)); // on prend d'abord les 8*sizeof(uint) bits a gauche et ensuite les suivant ect..
			  }
	}
	public static int sizeWithParity(int size, Raid raid) {
		return Stripe.computeNStripe(Block.computeNBlock(size), raid.getNbDisk())*Block.size;
	}
}
