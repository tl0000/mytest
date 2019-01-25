//#include "sqlite3.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "facedeb.hpp"
/*#define DEBUG*/
#include "facedb.hpp"

#define _DEBUG_


int main( void )
{	
	
	char buf[256] ;
	char *pbuf = (char*)buf;
	int len = 10;
	sqlite3 *db=NULL;	
	char *zErrMsg = 0; 
	sqlite3_stmt *stmt;	
	int rc; 	
	for(int i=0;i<256;i++)
	{
		buf[i] = i;
	}

	facedb faceiddb;
	rc = faceiddb.FaceDb_Open("face.db",&db);
	if( rc )	
	{		
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));		
		sqlite3_close(db);		
		return 0;	
	}	

	char psql[512];
#if 0
	sprintf(psql," CREATE TABLE faceid(\
	ID INTEGER PRIMARY KEY,\
	faceid INTEGER,\
	facename TEXT(32),\
	feature BLOB(1024)\
	);");

	faceiddb.Facedb_Createtable(db,psql,&zErrMsg);
#endif

	faceiddb.Facedb_Createtable(db,"ddddf",&zErrMsg);
	#ifdef _DEBUG_		
	printf("zErrMsg = %s \n", zErrMsg);	
	#endif 	//插入数据 
	faceiddb.FaceDb_Insert(db,stmt,"ddddf",1,"dd",pbuf,20);
	faceiddb.FaceDb_Insert(db,stmt,"ddddf",2,"ff",pbuf,20);
	faceiddb.FaceDb_Insert(db,stmt,"ddddf",6,"hh",pbuf,20);
	faceiddb.FaceDb_Insert(db,stmt,"ddddf",8,"yy",pbuf,20);
#if 0
	sprintf(psql, "insert into faceid values(NULL,1,'126',?)"); 
	faceiddb.FaceDb_Insert(db,stmt,psql,pbuf,102);
	sprintf(psql, "insert into faceid values(NULL,2,'nihao',?)"); 
	faceiddb.FaceDb_Insert(db,stmt,psql,pbuf,102);
	sprintf(psql, "insert into faceid values(NULL,3,'gaotie',?)"); 
	faceiddb.FaceDb_Insert(db,stmt,psql,pbuf,102);
	sprintf(psql, "insert into faceid values(NULL,4,'gaotie',?)"); 
	faceiddb.FaceDb_Insert(db,stmt,psql,pbuf,102);
#endif
	faceiddb.FaceDb_Delete(db,"ddddf",1,&zErrMsg);
	faceiddb.FaceDb_Delete(db,"ddddf","yy", &zErrMsg);

	//faceiddb.FaceDb_UpdataIDbyname(db,"ddddf","ff",1,&zErrMsg);
	//faceiddb.FaceDb_UpdatanamebyID(db,"ddddf","hello",1,&zErrMsg);

	//faceiddb.FaceDb_Delete(db,"ddddf",&zErrMsg);
	for(int i=0;i<256;i++)
	{
		buf[i] = 0x02;
	}

	//faceiddb.FaceDb_Update_feature(db,"ddddf",1,pbuf,20,&zErrMsg);
	//faceiddb.FaceDb_Update_feature(db,"ddddf","hh",pbuf,20,&zErrMsg);

	int userid;
	char name[32];
	char ppbuf[1024];
	int llen;
	//faceiddb.FaceDb_SearchIDbyname(db,stmt,"ddddf","hh",&userid);
	//faceiddb.FaceDb_SearchnamebyID(db,stmt,"ddddf",6,name);
	//faceiddb.FaceDb_SearchfeaturebyID(db,stmt,"ddddf",6,ppbuf,&llen);
	//faceiddb.FaceDb_Searchfeaturebyname(db,stmt,"ddddf","ff",ppbuf,&len);
	 //faceiddb.FaceDb_Search(db,stmt,"ddddf","ff",2,ppbuf,&llen);
	//faceiddb.Getcount(db,stmt,"ddddf");
//	sprintf(psql,"DELETE FROM faceid WHERE facename = 'nihao';");
//	faceiddb.FaceDb_Delete( db , psql ,&zErrMsg ); 
//	faceiddb.FaceDb_Close(db);

//	UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6;
/*
	rc = sqlite3_open("faceID.db", &db); //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件	
	if( rc )	
	{		
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));		
		sqlite3_close(db);		
		return 0;	
	}	
	char *sql = " CREATE TABLE faceinf(\
	ID INTEGER PRIMARY KEY,\
	FaceID INTEGER,\
	Name TEXT(32),\
	Feature BLOB(1024)\
	);" ;	
	sqlite3_exec( db , sql , NULL , NULL , &zErrMsg ); 	
	#ifdef _DEBUG_		
	printf("zErrMsg = %s \n", zErrMsg);	
	#endif 	//插入数据 	
	char psql[512];
	*/
/*
	char buf[255] = {0};	
	int len = sprintf(buf, "All the Fuel Level is %4.2f", buf[0]);	
	for (int i = 1; i < len; i++)	
	{		
		len += sprintf(buf + len, ", %4.2f", buf[i]);	
	}
*/
/*
	sprintf(psql, "insert into faceinf values(NULL,1,'126',?)");    
	   
	rc = sqlite3_prepare(db, psql, strlen(psql), &stmt, NULL);    
	if (rc != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", rc, sqlite3_errmsg(db));        
		sqlite3_close(db);        
		return -1;    
	}

 	rc = sqlite3_bind_blob(stmt, 1, &pbuf, 16, NULL);    
 	if (rc != SQLITE_OK) 
 	{        
 		fprintf(stderr, "db bind fail, errcode[%d], errmsg[%s]\n", rc, sqlite3_errmsg(db));        
 		sqlite3_close(db);        
 		return -1;    
 	} 

 	rc = sqlite3_step(stmt);    
 	if (rc != SQLITE_DONE) 
 	{        
 		fprintf(stderr, "db insert fail, errcode[%d], errmsg[%s]\n", rc, sqlite3_errmsg(db));        
 		sqlite3_close(db);        
 		return -1;    
 	}     
 	sqlite3_finalize(stmt);
	//sqlite3_close(db); //关闭数据库return 0; 

 	//int sqlite_find_count(sqlite3 *db)

	memset(psql,0,512);
	sprintf(psql, "select FaceID, Name ,Feature from faceinf");
	rc = sqlite3_prepare(db, psql, strlen(psql), &stmt, NULL);    
	if (rc != SQLITE_OK) 
	{        
		fprintf(stderr, "db prepare fail, errcode[%d], errmsg[%s]\n", rc, sqlite3_errmsg(db));        
		sqlite3_close(db);        
		return -1;    
	}     
       
	rc = sqlite3_step(stmt);        
	if (rc == SQLITE_ROW) 
	{            
		int id, id1, len,len1;            
		void *content = NULL;    
		void *content1 = NULL;          
		struct facedata *facedt = NULL;           
		int ID ;          
		char name[32];
		int feature[256];                             
		id = sqlite3_column_int(stmt, 0);   //ID


		content = (void *)sqlite3_column_text(stmt, 1); //name        
		len = sqlite3_column_bytes(stmt, 1);       
		char *pdat = (char*)content;

		content1 = (void *)sqlite3_column_blob(stmt, 2);//feature            
		len1 = sqlite3_column_bytes(stmt, 2);            
		//facedt = (struct facedata *)content;   
		float *pdat1 = (float*)content1;
		char datab[256];
		float *pdatab = (float*)datab;
		memcpy(datab,content,16);
		printf("ssssssss%f\n",pdatab[0] );
		//printf("ID=%d, name =%s , feature %d \n", facedt->ID , facedt->name,facedt->feature[2]);   
		printf("id = %d   namelen = %d  fealen1 = %d name = %s\n",id,len,len1,pdat);    
		for(int i=0;i<32;i++)
		{
			printf("%f ", pdat1[i]);
			if(i%4 == 3)
				printf("\n");
		}  
		printf("\n");   
 
		    
	} 
	else if (rc == SQLITE_DONE) 
	{            
		printf("select done!\n");                  
	} 
	else 
	{            
		fprintf(stderr, "db step fail, errcode[%d], errmsg[%s]\n", rc, sqlite3_errmsg(db));                   
	}    
	   
	sqlite3_finalize(stmt);
*/
	sqlite3_close(db); //关闭数据库return 0; 
	
}
