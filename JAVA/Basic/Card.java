package Basic;

public class Card {
	public enum Content {
		CC_PREVENT,//别学了(杀)0
		CC_DENY,//没学(闪)1
		CC_STUDY//学习(桃)2
	}
	public enum Color {
		CC_HEART,
		CC_SQUARE,
		CC_SPADE,
		CC_CLUB
	}
	
	private int number;
	private Content cont;
	private Color color;
	
	public Card(int n, int cont, int color) {
		number = n-1;
		switch(cont) {
		case 0:
			this.cont = Content.CC_PREVENT;
			break;
		case 1:
			this.cont = Content.CC_DENY;
			break;
		case 2:
			this.cont = Content.CC_STUDY;
			break;
		}
		switch(color){
		case 0:
			this.color = Color.CC_HEART;
			break;
		case 1:
			this.color = Color.CC_SQUARE;
			break;
		case 2:
			this.color = Color.CC_SPADE;
			break;
		case 3:
			this.color = Color.CC_CLUB;
			break;
		}
	}
}
