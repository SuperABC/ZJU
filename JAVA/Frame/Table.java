package Frame;

import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Toolkit;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import Basic.Card;
import Killer.Commander;
import Util.CardView;
import Util.ImageComp;
import Util.TextComp;

public class Table extends JFrame {
	
	ImageComp head, head1, head2, card1, card2;
	JTextArea input, chat;
	JButton send, confirm, cancel;
	
	Commander player, enemy1, enemy2;
	ArrayList<CardView> card = new ArrayList<>();
	
	public Table(int idx) {
		//Set Window Outlook.
		Toolkit kit = Toolkit.getDefaultToolkit();
		Dimension screenSize = kit.getScreenSize();
		setLocation((int)(screenSize.getWidth()/2-320),
				(int)(screenSize.getHeight()/2-240));
		setSize(646, 504);
		setResizable(false);
		setLayout(null);

		//Set backGround.
		ImageIcon background;
		background = new ImageIcon(Main.srcPath + "bg.png");
		JLabel bgLabel = new JLabel(background);
		getLayeredPane().add(bgLabel, new Integer(Integer.MIN_VALUE));
		bgLabel.setBounds(0,0,background.getIconWidth(), background.getIconHeight());
		Container cp=getContentPane(); 
		((JPanel)cp).setOpaque(false);
		
		input = new JTextArea();
		input.setBounds(10, 430, 530, 30);
		input.setFont(new Font("Î¢ÈíÑÅºÚ", Font.PLAIN, 20));
		add(input);
		chat = new JTextArea("Message History:");
		chat.setBounds(490, 210, 140, 210);
		chat.setEditable(false);
		chat.setForeground(new Color(63, 63, 63));
		chat.setBackground(new Color(192, 192, 192));
		add(chat);
		send = new JButton("send");
		send.setBounds(550, 430, 80, 30);
		add(send);
		confirm = new JButton("confirm");
		confirm.setBounds(80, 215, 90, 20);
		add(confirm);
		cancel = new JButton("cancel");
		cancel.setBounds(180, 215, 90, 20);
		add(cancel);
		card1 = new ImageComp("back.png");
		card1.setBounds(80, 10, 93, 150);
		add(card1);
		card2 = new ImageComp("back.png");
		card2.setBounds(400, 10, 93, 150);
		add(card2);
		
		player = new Commander();
		enemy1 = new Commander();
		enemy2 = new Commander();
		switch(idx) {
		case 0:
			player.head = new ImageComp("zrsicon.png");
			player.head.setBounds(10, 210, 60, 60);
			enemy1.head = new ImageComp("gtxicon.png");
			enemy1.head.setBounds(10, 10, 60, 60);
			enemy2.head = new ImageComp("zzhicon.png");
			enemy2.head.setBounds(330, 10, 60, 60);
			break;
		case 1:
			player.head = new ImageComp("gtxicon.png");
			player.head.setBounds(10, 210, 60, 60);
			enemy1.head = new ImageComp("zzhicon.png");
			enemy1.head.setBounds(10, 10, 60, 60);
			enemy2.head = new ImageComp("zrsicon.png");
			enemy2.head.setBounds(330, 10, 60, 60);
			break;
		case 2:
			player.head = new ImageComp("zzhicon.png");
			player.head.setBounds(10, 210, 60, 60);
			enemy1.head = new ImageComp("zrsicon.png");
			enemy1.head.setBounds(10, 10, 60, 60);
			enemy2.head = new ImageComp("gtxicon.png");
			enemy2.head.setBounds(330, 10, 60, 60);
			break;
		}
		add(player.head);
		add(enemy1.head);
		add(enemy2.head);
		player.battery = new ImageComp("b4o4.png");
		player.battery.setBounds(10, 270, 60, 80);
		enemy1.battery = new ImageComp("b4o4.png");
		enemy1.battery.setBounds(10, 70, 60, 80);
		enemy2.battery = new ImageComp("b4o4.png");
		enemy2.battery.setBounds(330, 70, 60, 80);
		add(player.battery);
		add(enemy1.battery);
		add(enemy2.battery);
		
		card.add(new CardView(0, 0, 0).setPos(80, 270));
		add(card.get(0));
		
	}

	

}