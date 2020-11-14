CREATE TABLE IF NOT EXISTS `estoque` (
  `codigo` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  `nome` TEXT NOT NULL,
  `quant` INTEGER NOT NULL,
  `preco` FLOAT NOT NULL
 );

 CREATE TABLE IF NOT EXISTS `vendas` (
  `idVenda` INTEGER NOT NULL,
  `codigo` INTEGER NOT NULL,
  `quant` INTEGER NOT NULL,
  `preco` FLOAT NOT NULL,
  PRIMARY KEY (`idVenda`, `codigo`)
);

insert into estoque (nome,quant,preco) values ('Agua              ', 10,1.5);
insert into estoque (nome,quant,preco) values ('Suco              ', 10,3);
insert into estoque (nome,quant,preco) values ('Tesoura           ', 10, 5);
insert into estoque (nome,quant,preco) values ('Caneta            ', 10, 0.5);
insert into estoque (nome,quant,preco) values ('Abajur            ', 5, 25);
insert into estoque (nome,quant,preco) values ('Batmovel          ', 2, 1000000);
insert into estoque (nome,quant,preco) values ('Criptonita        ', 50, 50);
insert into estoque (nome,quant,preco) values ('Esfera do Dragao  ', 7, 600);
insert into estoque (nome,quant,preco) values ('Semente dos Deuses', 20, 2500);
insert into estoque (nome,quant,preco) values ('Pocao             ', 100, 50);
insert into estoque (nome,quant,preco) values ('Super Pocao       ', 50, 200);

