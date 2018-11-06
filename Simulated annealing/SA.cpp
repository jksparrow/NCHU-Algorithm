 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>
 #include<math.h>
 #define T0 100.0  //��l�ū� 
 #define T_end 1 //�����ū� 
 #define q  0.98  //���ź� 
 #define L 1000  //���N���� 
 #define N 51 //�����ƶq 
 
 int city_list[N]; 
 double city_pos[N][2] = {
 {37,52},{49,49},{52,64},{20,26},{40,30},{21,47},{17,63},{31,62}, {52,33},{51,21},{42,41},{31,32},{5,25},{12,42},{36,16},{52,41}, {27,23},{17,33},{13,13},{57,58},{62,42},{42,57},{16,57},{8,52}, {7,38},{27,68},{30,48},{43,67},{58,48},{58,27},{37,69},{38,46}, {46,10},{61,33},{62,63},{63,69},{32,22},{45,35},{59,15},{5,6}, {10,17},{21,10},{5,64},{30,15},{39,10},{32,39},{25,32},{25,55}, {48,28},{56,37},{30,40}
 }; 
 
 double cal_distance(double *,double *);//�p��⫰���Z��
 double cal_path_len(int *);//�p����| 
 void  sa_init();//��l�� 
 void sa_create();//���;F�~ 
 
 //�p����I�Z�� 
 double cal_distance(double * city1,double * city2)
 {
 	double x1, x2, y1, y2, distance;
 	
    x1 = *city1;
    y1 = *(city1+1);
    x2 = *(city2);
    y2 = *(city2+1);
    distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    
    return distance;
 }
 
//�p���`���|�� 
 double cal_path_len(int * cp)
 {
     double total_path = 0; //�`���| 
     double each_dis = 0, last_dis= 0 ;
     int index1, index2, first_index, last_index;
     for(int i=0; i<N-1; i++)
     {
        index1 = *(cp+i);
        index2 = *(cp+i+1);
        each_dis = cal_distance(city_pos[index1-1],city_pos[index2-1]);
        total_path += each_dis;
     }
     //�[�W�̫�@�q����I���Z�� 
     first_index = *cp; //�Ĥ@�Ӯy�� 
     last_index = *(cp+N-1); //�̫�@�Ӯy�� 
     last_dis = cal_distance(city_pos[last_index-1],city_pos[first_index-1]);
     total_path += last_dis;
     
     return total_path; 
 }
 
 //��l�Ƥ@�� 
 void sa_init()
 {
     for(int i=0; i<N; i++)
     {
     	city_list[i] = i+1;
	 }
 }
 
//���;F�~ 
 void sa_create()
 {
 	double rnum1, rnum2;
 	int pos1, pos2, tmp;
 	//���o0~1���ü� 
    rnum1 = ((double)rand())/(RAND_MAX+1.0);
    rnum2 = ((double)rand())/(RAND_MAX+1.0);
    pos1 = (N*rnum1); 
    pos2 = (N*rnum2);
    //�洫��m 
    tmp = city_list[pos1];
    city_list[pos1] = city_list[pos2];
    city_list[pos2] = tmp; 
 }
 
 
 int main(void)
 {
    srand(time(NULL));
    time_t start,finish;
    double T = T0; //��l�ū� 
	int count = 0; //���Ŧ��� 
	int city_list_copy[N]; //�O�s�̪��
	double f1, f2, df, r; //�쥻�ȡB�s�ȡB�t�ȡB�H����(�O�_����) 
	
	start = clock(); 
	sa_init(); 
	while(T > T_end) //�C��̧C�ŴN����
	{
	    for(int i=0;i<L;i++)
	    {
	        memcpy(city_list_copy,city_list,sizeof(city_list)); 
	        sa_create(); 
	        f1 = cal_path_len(city_list_copy);
	        f2 = cal_path_len(city_list);
	        df = f2 - f1;
	        
	        if(df >= 0)
	        {
	            r = ((double)rand())/(RAND_MAX);
	            if(exp(-df/T) <= r) //�O�d��Ӫ���
	            {
	                memcpy(city_list,city_list_copy,sizeof(city_list_copy));
	            }
	        }
	    }
	    T *= q; // ���� 
	    count++;
	}
	finish = clock();
	double duration = ((double)(finish-start))/CLOCKS_PER_SEC; //�p��ɶ� 
	printf("��l�ū�T0=%.2f,\n���Ųvq=%.2f,\n�C�ӷū׭��N%d��,\n����%d��.\n",T0,q,L,count);
	printf("�̨�TSP���|:\n");
	
	for(int i=0; i<N-1; i++)
	{
	    printf("%d ", city_list[i]);
	}
	printf("%d\n", city_list[N-1]);
	double get_length = cal_path_len(city_list);
	printf("�̨θ��|����:%lf\n",get_length);
	printf("�ɶ���O:%lf��.\n",duration);
	
  return 0;
 }
