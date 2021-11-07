
// int getSql()
// {
// 	//  Iniciando vari�veis de conex�o, resultado e linha
// 	MYSQL* conn;
// 	MYSQL_RES* res;
// 	MYSQL_ROW row;
// 	unsigned int num_fields;
// 	MYSQL_FIELD* fields;
// 	int i = 0;
// 	int index = 0;
// 	//  Preenchendo dados do banco
// 	char* server = "20.121.202.26";
// 	char* user = "usuarioc";
// 	char* password = "145902";
// 	char* database = "dados";
// 	//  Inicia conex�o com banco
// 	conn = mysql_init(NULL);
// 	mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
// 	//  Executa Query
// 	mysql_query(conn, "SELECT lat AS latitude, lon AS longitude FROM dados_geo LIMIT 10;");
// 	//  Usa e printa resultado
// 	res = mysql_use_result(conn);
// 	num_fields = mysql_num_fields(res);
// 	fields = mysql_fetch_fields(res);
// 	for (i = 0; i < num_fields; i++)
// 	{
// 		//printf("Field %u is %s\n", i, fields[i].name);
// 		while ((row = mysql_fetch_row(res))) {

// 			lat[index] = atoi(row[i]);
// 			lon[index] = atoi(row[i + 1]);
// 			//printf("%d\n", lat[i]);
// 			//printf("%d\n", lon[i+1]);
// 			//printf("%s: %s\n",fields[i].name, row[i]);
// 			//printf("%s: %s\n",fields[i + 1].name, row[i + 1]);
// 			index++;
// 		}
// 	}
// 	//  Fecha conex�o e limpa o resultado
// 	//mysql_free_result(conn);
// 	//mysql_close(conn);
// }
