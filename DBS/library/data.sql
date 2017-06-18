IF NOT EXISTS(SELECT * FROM master..sysdatabases WHERE name='TSG')
  Create Database TSG
GO

USE TSG
GO

IF object_id('dbo.Lend') is not null DROP TABLE Lend
IF object_id('dbo.Book') is not null DROP TABLE Book
IF object_id('dbo.Patron') is not null DROP TABLE Patron
GO

CREATE TABLE Book (
  CallNo CHAR(20) CONSTRAINT PK_CallNo PRIMARY KEY,
  Title VARCHAR(50) CONSTRAINT NL_Title NOT NULL,
  Author CHAR(10),
  Publisher CHAR(20),
  ISBN CHAR(17) CONSTRAINT UE_ISBN UNIQUE,
  PubDate SMALLINT,
  Pages INT,
  Price NUMERIC(10,2),
  Number INT,
  AvailableNumber INT,
CONSTRAINT CK_Number CHECK(AvailableNumber<=Number));

INSERT Book VALUES('B848.4/Y828','ı����','����','�廪��ѧ������','978-7-302-19913-7',2009,250,29.8,3,2);
INSERT Book VALUES('C52/J181B:7','����������¼','������','�й����г�����','978-7-5074-2192-7',2010,234,29.00,4,4);
INSERT Book VALUES('D669.2/Z027','����ת���ھ�ҵǱ���о�','��ѧ��','����ʦ����ѧ������','978-7-303-20626-4',2010,284,20.00,2,1);
INSERT Book VALUES('F062.4/P220','����ѡ�񡢹��ʲ�ƽ���뾭�÷�չ','��ʿԶ','�㽭��ѧ������','978-7-308-07040-9',2009,147,25.00,5,5);
INSERT Book VALUES('F113.4/X291','����Σ���µľ��ñ��','��־ǿ','�й���֯������','978-7-5064-5428-5',2009,209,38.00,5,3);
INSERT Book VALUES('F121/L612','����ѧ����','��־ǿ','����ѧ���׳�����','978-7-5097-2057-9',2009,315,59.00,2,2);
INSERT Book VALUES('G0/Z810','�����Ļ�����������','��־ǿ','�ߵȽ���������','978-7-04-024397-0',2009,238,39.00,2,2);
INSERT Book VALUES('H152.2/Y750','������д����ս��','�൳��','�Ϻ��������³�����','978-7-5452-0446-9',2009,226,26.00,2,2);
INSERT Book VALUES('I222/C380','����ʫ��','������','�Ϻ��ż�������','978-7-5352-5262-7',2009,35,58.00,3,3);
INSERT Book VALUES('J212.05/W384','���ʯ�黭����','����÷','ɽ������������','978-7-5330-6754-4',2009,196,58.00,3,2);
INSERT Book VALUES('J305.1/Z150A','�����ִ�����','������','ɽ������������','978-7-5330-2929-6',2009,140,38.00,3,3);
INSERT Book VALUES('K092/Z120','�������˼����ʷѧ�о�','�Ž�ƽ','���������','978-7-01-007977-6',2009,448,60.00,3,3);
INSERT Book VALUES('K249.07/W470','��ʷʮ����','����','�л����','978-7-101-06365-3',2009,231,29.00,5,5);
INSERT Book VALUES('K257.03/L970-2','�ѱ��еĴ���','��־��','�л����','978-7-101-06633-3',2009,26,32.00,5,5);
INSERT Book VALUES('K712/LP950','������ʷͨ��','������','����ӡ���','978-7-100-05979-4',2009,355,23.00,4,4);
INSERT Book VALUES('K917/M074','��ʧ���Ļ��Ų�','��','�й����г�����','978-7-5074-2044-9',2009,211,27.00,5,5);
INSERT Book VALUES('N092/P140A','�칤���ﵼ��','�˼���','�й����ʹ�','978-7-5078-3008-8',2009,207,24.00,4,4);
INSERT Book VALUES('TB476/Z345','��ҵ���ģ������','����','��������ѧ������','978-7-5640-1833-7',2009,129,20.00,3,2);
INSERT Book VALUES('TB482/W090','��Ʒ��װ���','����','���ϴ�ѧ������','978-7-5641-1486-2',2009,316,99.00,5,4);
INSERT Book VALUES('TP311.138SQ/J276','MySQL���ܵ�����ܹ����','����','���ӹ�ҵ������','978-7-121-08740-0',2009,392,59.8,5,5);
--INSERT Book VALUES('','','','','',,,,,);

CREATE TABLE Patron (
  PatronID CHAR(11) CONSTRAINT PK_PatronID PRIMARY KEY,
  Name CHAR(10) CONSTRAINT NL_Name NOT NULL,
  Gender CHAR(2) CONSTRAINT CK_Gender CHECK(Gender='��' OR Gender='Ů'),
  BirthDate DATE,
  Type VARCHAR(10) CONSTRAINT NL_Type NOT NULL,
  Department VARCHAR(40) CONSTRAINT NL_Department NOT NULL);

INSERT Patron VALUES('S0120090101','������','Ů','1989-06-02','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090102','�����','��','1990-09-02','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090103','������','Ů','1990-04-29','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090201','���','Ů','1990-03-24','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090202','�ֺ쾲','Ů','1989-11-07','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090203','������','��','1991-05-01','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090204','���Ľ�','Ů','1991-11-04','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0120090205','������','��','1991-01-16','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0420090101','�����','��','1989-07-26','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0420090102','����','��','1990-02-14','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0420090103','֣ΰΰ','��','1991-06-09','ѧ��','����ѧԺ');
INSERT Patron VALUES('S0420090104','�ͱ�','��','1990-09-29','ѧ��','����ѧԺ');
INSERT Patron VALUES('T0101','���׻�','��','1966-03-05','��ʦ','����ѧԺ');
INSERT Patron VALUES('T0103','�򽡷�','Ů','1965-05-03','��ʦ','����ѧԺ');
INSERT Patron VALUES('T0201','������','Ů','1980-06-06','��ʦ','����ѧԺ');
INSERT Patron VALUES('T0202','����','Ů','1972-10-26','��ʦ','����ѧԺ');
--INSERT Patron VALUES('','','','','','');


CREATE TABLE Lend (
  CallNo CHAR(20) REFERENCES Book(CallNo),
  PatronID CHAR(11) REFERENCES Patron(PatronID),
  LendTime SMALLDATETIME DEFAULT getdate(),
  ReturnTime SMALLDATETIME,
  PRIMARY KEY(CallNo, PatronID, LendTime));

INSERT Lend VALUES('B848.4/Y828','S0120090101','2010-09-15 09:41:00','2010-11-07 14:36:00');
INSERT Lend VALUES('B848.4/Y828','S0120090103','2010-10-12 12:07:00',null);
INSERT Lend VALUES('C52/J181B:7','S0120090103','2010-08-17 16:10:00','2010-09-19 10:05:00');
INSERT Lend VALUES('D669.2/Z027','S0120090103','2010-02-09 14:12:00',null);
INSERT Lend VALUES('F113.4/X291','T0201','2010-06-10 14:09:00',null);
INSERT Lend VALUES('F121/L612','S0120090103','2009-11-14 16:24:00','2009-11-15 13:18:00');
INSERT Lend VALUES('F121/L612','T0103','2009-10-19 10:48:00','2009-11-04 12:27:00');
INSERT Lend VALUES('G0/Z810','S0120090204','2009-05-18 10:40:00','2009-06-09 13:19:00');
INSERT Lend VALUES('G0/Z810','S0120090101','2009-09-22 10:37:00','2009-10-17 16:44:00');
INSERT Lend VALUES('J212.05/W384','T0202','2010-09-19 10:57:00',null);
INSERT Lend VALUES('J305.1/Z150A','S0120090204','2010-06-08 14:00:00','2010-06-19 15:30:00');
INSERT Lend VALUES('J305.1/Z150A','T0103','2009-06-11 16:24:00','2009-06-07 16:23:00');
INSERT Lend VALUES('K249.07/W470','S0120090103','2009-09-12 10:46:00','2009-09-27 16:40:00');
INSERT Lend VALUES('K249.07/W470','T0101','2010-10-26 11:26:00','2010-10-30 13:42:00');
INSERT Lend VALUES('K712/LP950','T0201','2010-06-11 11:28:00','2010-06-21 10:36:00');
INSERT Lend VALUES('K917/M074','S0120090101','2009-09-04 11:50:00','2009-09-28 10:18:00');
INSERT Lend VALUES('N092/P140A','S0120090202','2010-04-06 15:52:00','2010-04-19 08:32:00');
INSERT Lend VALUES('N092/P140A','T0101','2010-01-13 08:57:00','2010-01-27 08:38:00');
INSERT Lend VALUES('TB476/Z345','S0120090102','2009-06-09 14:18:00','2009-06-30 10:04:00');
INSERT Lend VALUES('TB476/Z345','S0420090104','2010-06-10 10:49:00','2010-06-17 10:49:00');
INSERT Lend VALUES('TB476/Z345','S0420090104','2010-09-19 10:48:00',null);
INSERT Lend VALUES('TB482/W090','S0420090101','2009-06-14 10:36:00','2009-06-19 11:37:00');
INSERT Lend VALUES('TB482/W090','S0420090104','2010-09-19 10:48:00',null);
--INSERT Lend VALUES('','','','');
