#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

void* intal_create(const char* str)
{
	if(str==NULL)
		return NULL;
	else
	{
		if(str[0]<'0' || str[0]>'9')
		{
			char *zero_str=(char *)malloc(sizeof(char)*2);
			zero_str[0]='0';
			zero_str[1]='\0';
			void *zero=(void *)zero_str;
			return zero;
		}
		else
		{
			int i=0,n=strlen(str);
			char *s=(char *)malloc(sizeof(char)*(n+1));
			if(s==NULL)
				return NULL;
			while((i<n) && (str[i]>='0' && str[i]<='9'))
			{
					s[i]=str[i];
					i++;
			}
			s[i]='\0';
			void *temp=(void *)s;
			return temp;
		}
	}
}

void intal_destroy(void* intal)
{
	if(intal==NULL)
		return;
	if(intal!=NULL)
	{
		char *s=intal2str(intal);
		free(s);
	}
}

char* intal2str(void* intal)
{
	if(intal==NULL)
	{
		char *NaN=(char *)malloc(sizeof(char)*4);
		strcpy(NaN,"NaN");
		return NaN;
	}	
	char *s=(char *)intal;
	//printf("%lu\n",strlen(s));
	char *str=(char *)malloc(sizeof(char)*strlen(s));
	strcpy(str,s);
	//printf("intal2str:%s\n",str);
	return str;
}

static void* truncate_zeros(void* intal)
{
  if(intal==NULL)
    return NULL;
  char *str=intal2str(intal);
  char *p=str;
  while((*(p+1)) && ((*p)=='0'))
  	p++;
  void *intal1=(void *)p;
  return intal1;
}

void* intal_increment(void* intal)
{
  if(intal==NULL)
      return NULL;
  void* intal1=intal_create("1");
	intal=truncate_zeros(intal);
  return intal_add(intal,intal1);
	/*
 if(intal==NULL)
		return NULL;
	int i,j,x,carry=1;
	char *str=intal2str(intal);
	str=(char *)realloc(str,sizeof(str)+sizeof(char));
	for(i=strlen(str)-1;i>=0;i--)
	{
		x=((str[i]-'0')+carry);
		str[i]=(x%10)+'0';
		carry=x/10;
  }
	if(str[0]=='0')
  {
  	for(j=strlen(str);j>=0;j--)
    	str[j+1] = str[j];
    str[0] = '1';
  }
  return (void*)str;
	*/
}

void* intal_decrement(void* intal)
{
  if(intal==NULL)
      return NULL;
  if(intal_compare(intal,intal_create("0"))==0)
     return intal_create("0");
  void* intal1=intal_create("1");
	intal=truncate_zeros(intal);
  return intal_diff(intal,intal1);
	/*
 	if(intal==NULL)
		return NULL;
	int i,j,x,borrow=0,n;
	char *str=intal2str(intal);
	n=strlen(str);
	for(i=strlen(str)-1;i>=0;i--)
	{
		x=((str[i]-'0')+10-(1-borrow));
		str[i]=(x%10)+'0';
		borrow=x/10;      
  }
	while(str[0]=='0')
  {
  	for(j=0;j<n;j++)
    	str[j] = str[j+1];
    n--;
  }
	return (void*)str;
	*/
}

void* intal_add(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	if(intal_compare(intal1,intal_create("0"))==0)
		return (void *)intal2;
	if(intal_compare(intal2,intal_create("0"))==0)
		return (void *)intal1;
	intal1=truncate_zeros(intal1);
	intal2=truncate_zeros(intal2);
	int i,j=0,n,m,l,x,carry=0;
	char *str1,*str2;
	str1=intal2str(intal1);
	//printf("add_str1:%s\n",str1);
	str2=intal2str(intal2);
	//printf("add_str2:%s\n",str2);		
	if(intal_compare(intal1,intal2)==1)
	{
		str1=intal2str(intal2);
		//printf("add_str1:%s\n",str1);
		str2=intal2str(intal1);
		//printf("add_str2:%s\n",str2);
	}
	n=strlen(str1);
	m=strlen(str2);
	l=m-n;
	//printf("n:%d m:%d l:%d\n",n,m,l);
	char *sum=(char *)malloc(sizeof(char)*(m+2));
	sum[m+1]='\0';
	for(i=(n-1);i>=0;i--)
	{
		x=(((str1[i]-'0')+(str2[i+l]-'0'))+carry);
		sum[j++]=((x%10)+'0');
		//printf("sum=%c\n",sum[j]);
		carry=(x/10);
	}
	//printf("sum=%s\n",sum);
	//printf("i=%d\n",i);
	for(i=(m-n-1);i>=0;i--)
	{
		x=(str2[i]-'0')+carry;
		sum[j++]=((x%10)+'0');
		//printf("sum=%c\n",sum[j]);
		carry=(x/10);
	}
	//printf("sum=%s\n",sum);
	if(carry)
		sum[i]=(carry+'0');
	sum[j++]='\0';
	n=strlen(sum);
	for(int i=0;i<n/2;i++)
 {
	   char temp=sum[i];
	   sum[i]=sum[n-i-1];
	   sum[n-i-1]=temp;
	}
	void *add_result=(void *)sum;
  return truncate_zeros(add_result);
/*	
	while(sum[0]=='0')
  {
  	for(j=0;j<len;j++)
    	sum[j] = sum[j+1];
    len--;
  }
*/
	//return (void *)sum;
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	if(intal_compare(intal1,intal_create("0"))==0)
		return (void *)intal2;
	if(intal_compare(intal2,intal_create("0"))==0)
		return (void *)intal1;
	intal1=truncate_zeros(intal1);
	intal2=truncate_zeros(intal2);
	int i,j=0,n,m,l,x,borrow=0;
	char *str1,*str2;
	str1=intal2str(intal1);
	//printf("diff_str1:%s\n",str1);
	str2=intal2str(intal2);
	//printf("diff_str2:%s\n",str2);		
	if(intal_compare(intal1,intal2)==-1)
	{
		str1=intal2str(intal2);
		//printf("diff_str1:%s\n",str1);
		str2=intal2str(intal1);
		//printf("diff_str2:%s\n",str2);
	}
	n=strlen(str1);
	m=strlen(str2);
	l=n-m;
	char *diff=(char *)malloc(sizeof(char)*(n+1));
	diff[n+1]='\0';
	for(i=(m-1);i>=0;i--)
	{
		x=((str1[i+l]-'0')-(str2[i]-'0')-borrow);
		if(x<0)
		{
			x+=10;
			borrow=1;
		}
		else
			borrow=0;
		diff[j++]=(x+'0');
	}
	//printf("diff=%s\n",diff);
	//printf("i=%d\n",i);
	for(i=(n-m-1);i>=0;i--)
	{
		if(str1[i]=='0' && borrow)
		{
			diff[j++]='9';
			continue;
		}
		x=((str1[i]-'0')-borrow);
		if(i>0 || x>0)
			diff[j++]=(x+'0');
		borrow=0;
	}
	diff[j++]='\0';
	//printf("diff=%s\n",diff);
	n=strlen(diff);
	for(int i=0;i<n/2;i++)
 	{
	   char temp=diff[i];
	   diff[i]=diff[n-i-1];
	   diff[n-i-1]=temp;
	}
	void *diff_result=(void *)diff;
	return truncate_zeros(diff_result);
/*
	while(diff[0]=='0')
  {
  	for(j=0;j<n;j++)
    	diff[j] = diff[j+1];
    n--;
  }
*/
}

static char *append_char(char *str, char c)
{
  int l=strlen(str);
  str[l]=c;
  str[l+1]='\0';
  return str;
}

static char *make_zeros(int l, int n)
{
  char *z=(char *)malloc(l+1);
  int i;
  for(i=0;i<n;i++)
  	*(z+i)='0';
  *(z+n)='\0';
  return z;
}

static char *shift(char *str, int n)
{
  int i,l=strlen(str);
  char *new_str=(char *)malloc(sizeof(char)*(l+n+1));
  strcpy(new_str,str);
  char *zeros=(char *)malloc(sizeof(char)*(n+1));
  strcpy(zeros,"");
  for(i=0;i<n;i++)
  	zeros = append_char(zeros,'0');
  strcat(new_str,zeros);
  return new_str;
}

static int equalize_length(void **intal1, void **intal2)
{
	char *s1=(char *)(*intal1);
	char *s2=(char *)(*intal2);
  int l1=strlen(s1);
  int l2=strlen(s2);
  int diff;
  if (l1>l2)
	{
    diff=l1-l2;
    char *zeros=make_zeros(l1,diff);
    strcat(zeros,s2);
    s2=zeros;
		return l1;
  }
  else if (l2>l1)
	{
    diff=l2-l1;
    char *zeros=make_zeros(l2, diff);
    strcat(zeros,s1);
    s1=zeros;
    return l2;
	}
	return l1;
}

static char *multiply(char* a, char* b)
{
	//printf("Inside Multiply\n");
	//printf("a:%s b:%s\n",a,b);
	int e=(*(char *)a-'0')*(*(char *)b-'0');
  if((e/10)!=0)
  {
    char *str=(char *)malloc(sizeof(char)*3);
    *str=(e/10)+'0';
    *(str+1)=(e%10)+'0';
    *(str+2)='\0';
    return str;
  }
  char *str=(char *)malloc(sizeof(char)*2);
  *str=(e%10)+'0';
  *(str+1)='\0';
  return str;
}

void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	int n=equalize_length(&intal1,&intal2);
	if(n==0)
		return (void *)"0";
	if(intal_compare(intal1,intal_create("1"))==0)
		return intal2;
	if(intal_compare(intal2,intal_create("1"))==0)
		return intal1;
	if(n==1)
		return (void *)multiply(intal1,intal2);
	int f=n/2;
	int mid=(n-f);
	char *a=(char *)malloc(sizeof(char)*mid);
	char *b=(char *)malloc(sizeof(char)*n);
	char *c=(char *)malloc(sizeof(char)*mid);
	char *d=(char *)malloc(sizeof(char)*n);
	strcpy(a,intal1);
	strcpy(b,intal1);
	strcpy(c,intal2);
	strcpy(d,intal2);
	*(a+f)='\0';
	b+=f;
	*(c+f)='\0';
	d+=f;
	//printf("a:%s b:%s c:%s d:%s\n",a,b,c,d);
	char *ab=intal_add(a,b);
	//printf("ab:%s\n",ab);
	char *cd=intal_add(c,d);
	//printf("cd:%s\n",cd);
	char *p0=intal_multiply(a,c);
	//printf("p0:%s\n",p0);
	char *p1=intal_multiply(b,d);
	//printf("p1:%s\n",p1);
	char *p2=intal_multiply(ab,cd);
	//printf("p2:%s\n",p2);
	char *t1=shift(p0,2*mid);
	//printf("t1:%s\n",t1);
	char *t2=intal_add(p0,p1);
	//printf("t2 after add before shift:%s\n",t2);
	t2=intal_diff(p2,t2);
	//printf("t2 after diff before shift:%s\n",t2);
	t2=shift(t2,mid);
	//printf("t2 after shift:%s\n",t2);
	//printf("t2:%s\n",t2);
	char *p3=intal_add(t1,t2);
	//printf("p3:%s\n",p3);
	char *P=intal_add(p1,p3);
	void *multiply_result=(void *)P;
	return truncate_zeros(multiply_result);
}

void* intal_divide(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	if(intal_compare(intal2,intal_create("0"))==0)
		return NULL;
	int cmp=intal_compare(intal1,intal2);
	if(cmp<0)
		return intal_create("0");
	else if(cmp==0)
		return intal_create("1");
	int l1=strlen(intal1),l2=strlen(intal2);
	char *div=(char *)malloc(sizeof(char)*l1);
	strcpy(div,"");
	char *str=(char *)malloc(sizeof(char)*l2);
	strncpy(str,intal1,l2);
	*(str+l2)='\0';
	int i,count;
	for(i=0;i<(l2-strlen(str)+1);i++)
	{
		count=0;
		while(intal_compare(str,intal2)>=0)
		{
			count++;
			str=intal_diff(str,intal2);
		}
		append_char(div,count+'0');
		if(i!=(l1-strlen(str)))
		{
			char *new_str=(char *)malloc(sizeof(char)*(strlen(str)+1));
			strcpy(new_str,str);
			append_char(new_str,*(char *)(intal1+strlen(str)+i));
			strcpy(str,new_str);
			free(new_str);
			str=intal_create(str);
		}
  }
	void *div_result=(void *)div;
  return truncate_zeros(div_result);
}

int intal_compare(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return 0;
	int n,m;
	char *str1=(char *)malloc(sizeof(intal1));
	str1=(char *)intal1;
	char *str2=(char *)malloc(sizeof(intal2));
  str2=(char *)intal2;
	char *p1=str1,*p2=str2;
  while((*p1) && ((*p1)=='0'))
  	p1++;
  while ((*p2) && ((*p2)=='0'))
    p2++;
  n=strlen(p1),
	m=strlen(p2);
  if(n>m)
     return 1;
  else if(n<m)
     return -1;
  else
  {
  	if(strcmp(p1,p2)==0)
    	return 0;
		else if(strcmp(p1,p2)>0)
    	return 1;
		else
    	return -1;
   }
}

void* intal_pow(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	if(intal_compare(intal1,intal_create("0"))==0)
		return intal_create("0");
	char *exp=(char *)malloc(sizeof(char)*10001);
	exp[10001]='\0';
	strcpy(exp,"1");
	while (intal_compare(intal2,intal_create("0"))>0)
	{
		if((*(char *)(intal2+strlen(intal2)-1)%2)!=0)
		{
			//printf("%s %s %s\n",intal1,intal2,exp);
			exp=intal_multiply(intal1,exp);
		}
		intal2=intal_divide(intal2,"2");
    intal1=intal_multiply(intal1,intal1);
 	}
 	void *pow_result=(void *)exp;
	return truncate_zeros(pow_result);
}

