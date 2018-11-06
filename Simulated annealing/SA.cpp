 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>
 #include<math.h>
 #define T0 100.0  //初始溫度 
 #define T_end 1 //結束溫度 
 #define q  0.98  //降溫綠 
 #define L 1000  //迭代次數 
 #define N 51 //城市數量 
 
 int city_list[N]; 
 double city_pos[N][2] = {
 {37,52},{49,49},{52,64},{20,26},{40,30},{21,47},{17,63},{31,62}, {52,33},{51,21},{42,41},{31,32},{5,25},{12,42},{36,16},{52,41}, {27,23},{17,33},{13,13},{57,58},{62,42},{42,57},{16,57},{8,52}, {7,38},{27,68},{30,48},{43,67},{58,48},{58,27},{37,69},{38,46}, {46,10},{61,33},{62,63},{63,69},{32,22},{45,35},{59,15},{5,6}, {10,17},{21,10},{5,64},{30,15},{39,10},{32,39},{25,32},{25,55}, {48,28},{56,37},{30,40}
 }; 
 
 double cal_distance(double *,double *);//計算兩城市距離
 double cal_path_len(int *);//計算路徑 
 void  sa_init();//初始化 
 void sa_create();//產生鄰居 
 
 //計算兩點距離 
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
 
//計算總路徑長 
 double cal_path_len(int * cp)
 {
     double total_path = 0; //總路徑 
     double each_dis = 0, last_dis= 0 ;
     int index1, index2, first_index, last_index;
     for(int i=0; i<N-1; i++)
     {
        index1 = *(cp+i);
        index2 = *(cp+i+1);
        each_dis = cal_distance(city_pos[index1-1],city_pos[index2-1]);
        total_path += each_dis;
     }
     //加上最後一段到原點的距離 
     first_index = *cp; //第一個座標 
     last_index = *(cp+N-1); //最後一個座標 
     last_dis = cal_distance(city_pos[last_index-1],city_pos[first_index-1]);
     total_path += last_dis;
     
     return total_path; 
 }
 
 //初始化一組 
 void sa_init()
 {
     for(int i=0; i<N; i++)
     {
     	city_list[i] = i+1;
	 }
 }
 
//產生鄰居 
 void sa_create()
 {
 	double rnum1, rnum2;
 	int pos1, pos2, tmp;
 	//取得0~1的亂數 
    rnum1 = ((double)rand())/(RAND_MAX+1.0);
    rnum2 = ((double)rand())/(RAND_MAX+1.0);
    pos1 = (N*rnum1); 
    pos2 = (N*rnum2);
    //交換位置 
    tmp = city_list[pos1];
    city_list[pos1] = city_list[pos2];
    city_list[pos2] = tmp; 
 }
 
 
 int main(void)
 {
    srand(time(NULL));
    time_t start,finish;
    double T = T0; //初始溫度 
	int count = 0; //降溫次數 
	int city_list_copy[N]; //保存最初解
	double f1, f2, df, r; //原本值、新值、差值、隨機值(是否接受) 
	
	start = clock(); 
	sa_init(); 
	while(T > T_end) //低於最低溫就結束
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
	            if(exp(-df/T) <= r) //保留原來的解
	            {
	                memcpy(city_list,city_list_copy,sizeof(city_list_copy));
	            }
	        }
	    }
	    T *= q; // 降溫 
	    count++;
	}
	finish = clock();
	double duration = ((double)(finish-start))/CLOCKS_PER_SEC; //計算時間 
	printf("初始溫度T0=%.2f,\n降溫率q=%.2f,\n每個溫度迭代%d次,\n降溫%d次.\n",T0,q,L,count);
	printf("最佳TSP路徑:\n");
	
	for(int i=0; i<N-1; i++)
	{
	    printf("%d ", city_list[i]);
	}
	printf("%d\n", city_list[N-1]);
	double get_length = cal_path_len(city_list);
	printf("最佳路徑長度:%lf\n",get_length);
	printf("時間花費:%lf秒.\n",duration);
	
  return 0;
 }
