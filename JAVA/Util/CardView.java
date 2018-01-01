package Util;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

import Basic.Card;
import Frame.Main;

public class CardView extends JComponent {
	private Card c;
	private Image id, num, tex;
	private int posX = 0,  posY = 0;
	private int sizeX = 93, sizeY = 150;
	
	public CardView(int n, int cont, int color) {
		c = new Card(n, cont, color);
		switch(cont) {
		case 0:
			id = new ImageIcon(Main.srcPath + "prevent.png").getImage();
			break;
		case 1:
			id = new ImageIcon(Main.srcPath + "deny.png").getImage();
			break;
		case 2:
			id = new ImageIcon(Main.srcPath + "study.png").getImage();
			break;
		}
		switch(n) {
		case 0:
			num = new ImageIcon(Main.srcPath + "n1.png").getImage();
			break;
		case 1:
			num = new ImageIcon(Main.srcPath + "n2.png").getImage();
			break;
		case 2:
			num = new ImageIcon(Main.srcPath + "n3.png").getImage();
			break;
		case 3:
			num = new ImageIcon(Main.srcPath + "n4.png").getImage();
			break;
		case 4:
			num = new ImageIcon(Main.srcPath + "n5.png").getImage();
			break;
		case 5:
			num = new ImageIcon(Main.srcPath + "n6.png").getImage();
			break;
		case 6:
			num = new ImageIcon(Main.srcPath + "n7.png").getImage();
			break;
		case 7:
			num = new ImageIcon(Main.srcPath + "n8.png").getImage();
			break;
		case 8:
			num = new ImageIcon(Main.srcPath + "n9.png").getImage();
			break;
		case 9:
			num = new ImageIcon(Main.srcPath + "n10.png").getImage();
			break;
		case 10:
			num = new ImageIcon(Main.srcPath + "n11.png").getImage();
			break;
		case 11:
			num = new ImageIcon(Main.srcPath + "n12.png").getImage();
			break;
		case 12:
			num = new ImageIcon(Main.srcPath + "n13.png").getImage();
			break;
		}
		switch(color) {
		case 0:
			tex = new ImageIcon(Main.srcPath + "heart.png").getImage();
			break;
		case 1:
			tex = new ImageIcon(Main.srcPath + "square.png").getImage();
			break;
		case 2:
			tex = new ImageIcon(Main.srcPath + "spade.png").getImage();
			break;
		case 3:
			tex = new ImageIcon(Main.srcPath + "club.png").getImage();
			break;
		}
	}
	public CardView setPos(int x, int y) {
		posX = x;
		posY = y;
		setBounds(posX, posY, sizeX, sizeY);
		return this;
	}

	public void paintComponent(Graphics g) {
		if (id == null) return;
		g.drawImage(id, 0, 0, sizeX, sizeY, null);
		g.drawImage(num, 0, 0, sizeX, sizeY, null);
		g.drawImage(tex, 0, 0, sizeX, sizeY, null);
	}

	public Dimension getPreferredSize() {
		return new Dimension(sizeX, sizeY);
	}
}
