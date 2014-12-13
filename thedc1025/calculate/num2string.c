#include "mhc.h"
#include "GlobalVariables.h"

/**************************实现函数********************************************
函数原型：int16o_string(int16 data, char *string)
功　　能：将int16型数据转化成字符串，并添加到*string指向的字符串的末尾
输入参数：int16 data	需要转化的数据
		  char *string 	指向存放转换结果的字符串的指针
输出参数：无
注    意：保证存放转换结果的字符串长度足够不会溢出，结果会添加到字符串的末尾，
		  使用前，先把存放结果的字符串的无效数据清除
作    者：肖熙吉
版    本：1.0
日    期：2013-11-18
*******************************************************************************/
void int16_to_string(int16 data, char *string)
{ 
 char char_temp[11];
 int16 data_temp;
 Uint8 posi=0;
 Uint8 zeroflag=0;
 if(data<0)
 {
  data_temp=data*(-1);
  char_temp[0]='-';
  posi=1;
 }
 else
 {
  data_temp=data;
 }
 char_temp[posi]=data_temp/10000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100)/10+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10)+'0';	
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++;
// char_temp[posi]=SEPARATE;
// posi++;
 char_temp[posi]=0;
 strcat(string,char_temp);
}
/**************************实现函数********************************************
函数原型：uint32o_string(uint32 data, char *string)
功　　能：将uint32型数据转化成字符串，并添加到*string指向的字符串的末尾
输入参数：uint32 data	需要转化的数据
		  char *string 	指向存放转换结果的字符串的指针
输出参数：无
注    意：保证存放转换结果的字符串长度足够不会溢出，结果会添加到字符串的末尾，
		  使用前，先把存放结果的字符串的无效数据清除
作    者：肖熙吉
版    本：1.0
日    期：2013-11-18
*******************************************************************************/
void uint32_to_string(Uint32 data, char *string)
{ 
 char char_temp[14];
 Uint8 posi=0;
 Uint8 zeroflag=0;
 char_temp[posi]=data/1000000000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000000000)/100000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100000000)/10000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10000000)/1000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000000)/100000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100000)/10000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%100)/10+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data%10)+'0';	
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++; 
 char_temp[posi]=SEPARATE;
 posi++;
 char_temp[posi]=0;
 strcat(string,char_temp);
}
/**************************实现函数********************************************
函数原型：double_to_string(int16 data, char *string)
功　　能：将double型数据转化成字符串，并添加到*string指向的字符串的末尾
输入参数：double data	需要转化的数据
		  char *string 	指向存放转换结果的字符串的指针
输出参数：无
注    意：保证存放转换结果的字符串长度足够不会溢出，结果会添加到字符串的末尾，
		  使用前，先把存放结果的字符串的无效数据清除，转换结果在-99999.99到99999.99之间
		  精度0.01，超出范围的数据不能正确转换
作    者：肖熙吉
版    本：1.0
日    期：2013-11-18
*******************************************************************************/
void double_to_string(double data,char *string)
{
 char char_temp[21];
 int32 data_temp;
 Uint8 posi=0;
 Uint8 zeroflag=0;
if(data>0)
	{
	data_temp=(int32)(data*100);
	}
else  
	{
	char_temp[0]='-';
	posi=1;
	data_temp=(int32)(data*(-100));
	}
 char_temp[posi]=(data_temp%10000000000)/1000000000+'0';
 if(char_temp[posi]!='0')
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000000)/100000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000000)/10000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000000)/1000000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%1000000)/100000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%100000)/10000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
 char_temp[posi]=(data_temp%10000)/1000+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 posi++;
	 zeroflag=1;
	}
  char_temp[posi]=(data_temp%1000)/100+'0';
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]='.';
 posi++;
 char_temp[posi]=(data_temp%100)/10+'0'; 
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 posi++;
 char_temp[posi]=(data_temp%10)+'0';	
 if((char_temp[posi]!='0')||zeroflag)
	{
	 zeroflag=1;
	}
 if(zeroflag)
	 {
	 posi++; 
	 char_temp[posi]=SEPARATE;
	 posi++;
//	 char_temp[posi]=SEPARATE;
//	 posi++;
	 char_temp[posi]=0;
	 }
 else
	 {
	 char_temp[0]='0';
	 char_temp[1]=SEPARATE;
	 posi++;
//	 char_temp[2]=SEPARATE;
//	 posi++;
//	 char_temp[3]=0;
	 char_temp[2]=0;
	 }
 strcat(string,char_temp);
}




//
///**************************实现函数********************************************
//函数原型：void string_to_command(char *string,COMMAND_TypeDef *command)
//功　　能：将命令字符串截成double型命令数据
//输入参数：COMMAND_TypeDef command	指向转换后的结果的指针
//		  char *string 	指向存放源字符串的指针
//输出参数：无
//作    者：肖熙吉
//版    本：1.0
//日    期：2013-11-19
//*******************************************************************************/
//void string_to_command(char *string,COMMAND_TypeDef *command)
//{
// double data=0,temp=0,mul=0.1;
// char cmd[4];
// char *p=string;
// Uint8 data_num_count=0;
// Uint8 signe=0;
// Uint8 string_stata=0;
// if(*p=='$')
//	{
//	  p++;
//	  while((*p>='a'&&*p<='z')||(*p>='A'&&*p<='Z'))
//		  {
//
//		  cmd[data_num_count]=*p;
//		  if(data_num_count<2)
//		  	 data_num_count++;
//			 p++;
//		  }
//		data_num_count++;
//		cmd[data_num_count]=0;
//		data_num_count=0;
//	  	if(*p==RECEIVE_SEPARATE)
//		   	 {
//			  p++;
//			  while((*p=='-')||(*p>='0'&&*p<='9')||(*p==RECEIVE_SEPARATE))
//				{
//				  signe=0;
//				  mul=0.1;
//				  data=0;
//				  temp=0;
//				  if(*p=='-')
//				  	{
//					if(string_stata==0)
//			          {
//					  signe=1;
//					  p++;
//					  }
//					else
//						return ;
//					}
//		          while(*p>='0'&&*p<='9')
//					 {
//					 temp=(double)(*p-'0');
//					 data=data*10;
//					 data=data+temp;
//					 p++;
//					 string_stata=1;
//					 }
//				 if(*p=='.')
//					{
//					if(string_stata==1)
//					  {
//					  p++;
//					  while(*p>='0'&&*p<='9')
//						 {
//						 temp=(double)(*p-'0');
//						 data=data+temp*mul;
//						 mul*=0.1;
//						 p++;
//						 }
//					  string_stata=2;
//					  }
//					else return;
//					}
//				 if(*p==RECEIVE_SEPARATE)
//					{
//					if(signe==1)
//					   data=0-data;
//
//					if(0==strcmp(cmd,"Pit"))
//						{
//						if(string_stata)
//							{
//							command->Pitch[data_num_count]=data;
//							(command->Send)|=0x20;
//							}
//						if(6>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Rol"))
//						{
//						if(string_stata)
//							{
//							command->Roll[data_num_count]=data;
//						    (command->Send)|=0x40;
//							}
//						if(6>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Yaw"))
//						{
//						if(string_stata)
//							{
//							command->Yaw[data_num_count]=data;
//							(command->Send)|=0x80;
//							}
//
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Alt"))
//						{
//						if(string_stata)
//							{
//							command->Alt[data_num_count]=data;
//							(command->Send)|=0x100;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Nor"))
//						{
//						if(string_stata)
//							{
//							command->Sn[data_num_count]=data;
//							(command->Send)|=0x200;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					if(0==strcmp(cmd,"Eas"))
//						{
//						if(string_stata)
//							{
//							command->Se[data_num_count]=data;
//							(command->Send)|=0x400;
//							}
//						if(4>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					 if(0==strcmp(cmd,"Ser"))
//						{
//						if(string_stata)
//							{
//							command->Ser[data_num_count]=data;
//							(command->Send)|=0x800;
//							}
//						if(2>data_num_count)
//							data_num_count++;
//						else return;
//						}
//					  if(0==strcmp(cmd,"Sen"))
//						{
//						if(string_stata)
//							{
//							command->Send=(Uint32)data;
//							}
//				        return;
//						}
//
//					p++;
//					string_stata=0;
//					}
//				 if(*p=='*')return;
//				 }
//			 }
//
//	}
//
//}

/**************************实现函数********************************************
函数原型：string_to_one_double(char *string,double *data)
功　　能：特定格式的字符串转换成double型数据
输入参数：double *data	指向转换后的结果的指针
		  char *string 	指向存放源字符串的指针
输出参数：无
作    者：肖熙吉
版    本：1.0
日    期：2013-11-26
*******************************************************************************/		
void string_to_one_double(char *string,double *data)
{
 double tempf=0;
 Uint8 bits=0;
 Uint8 signe=0;
 double mul=0.1;

 if(string[bits]=='-')
 {
  signe=1;
  bits++; 
 }
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 tempf=tempf*10+(string[bits]-'0');
	 bits++;
	 }
 if(string[bits]=='.')
 {
 bits++;
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 tempf+=mul*(string[bits]-'0');
	 mul*=0.1;
	 bits++;
	 }
 if(signe)
   *data=-tempf;	
 else
   *data=tempf;
 }
}

/**************************实现函数********************************************
函数原型：string_to_one_double(char *string,double *data)
功　　能：特定格式的字符串转换成int32型数据
输入参数：int32 *data	指向转换后的结果的指针
		  char *string 	指向存放源字符串的指针
输出参数：无
作    者：肖熙吉
版    本：1.0
日    期：2013-11-26
*******************************************************************************/
void string_to_one_int32(char *string,int32 *data)
{
 double temp_32=0;
 Uint8 bits=0;
 Uint8 signe=0;
 if(string[bits]=='-')
 {
  signe=1;
  bits++; 
 }
 while(string[bits]<='9'&&string[bits]>='0')
	 {
	 temp_32=temp_32*10+(string[bits]-'0');
	 bits++;
	 }
 if(signe)
 	*data=-temp_32;
 else
  	*data=temp_32;

}
