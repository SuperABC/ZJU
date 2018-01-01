package Util;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

import Frame.Main;

public class ImageComp extends JComponent {
	private Image image;
	private int posX = 0,  posY = 0;
	private int sizeX = 0, sizeY = 0;
	
	public ImageComp(String imgName) {
		image = new ImageIcon(Main.srcPath + imgName).getImage();
		this.sizeX = image.getWidth(this);
		this.sizeY = image.getHeight(this);
		setBounds(posX, posY, sizeX, sizeY);
	}
	public ImageComp(String imgName, int x, int y) {
		image = new ImageIcon(Main.srcPath + imgName).getImage();
		this.posX = x;
		this.posY = y;
		this.sizeX = image.getWidth(this);
		this.sizeY = image.getHeight(this);
		setBounds(posX, posY, sizeX, sizeY);
	}
	public ImageComp(String imgName, int x, int y, int w, int h) {
		image = new ImageIcon(Main.srcPath + imgName).getImage();
		this.posX = x;
		this.posY = y;
		this.sizeX = w;
		this.sizeY = h;
		setBounds(posX, posY, sizeX, sizeY);
	}
	
	public void paintComponent(Graphics g) {
		if (image == null) return;
		g.drawImage(image, 0, 0, sizeX, sizeY, null);
	}

	public Dimension getPreferredSize() {
		return new Dimension(sizeX, sizeY);
	}
}