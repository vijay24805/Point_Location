#include <stdio.h>
#include <stdlib.h>
#include<time.h>
# define ZERO 999999999;

typedef int ploc_t;

int length_indp_set = 0;
int indp_set_length;

// global declaration //
int new_index = 0;

int step = 0;

int step_or = 0;

int tri_start[20];
int ts = 0;
int re_tri = 0;
// global declaration //

int or_test(int *p, int *q, int *x, int *points) {

	long result1 = 0;
	long result = 0;
	int result_f = 0;

	int *point = points;

	int px = point[(*p) * 2];
	int py = point[((*p) * 2) + 1];
	int qx = point[(*q) * 2];
	int qy = point[((*q) * 2) + 1];
	int xx = point[(*x) * 2];
	int xy = point[((*x) * 2) + 1];

	//printf("px/py (%d,%d) ,qx/qy (%d,%d) ,xx/xy(%d,%d)\n", px, py, qx, qy, xx,xy);
	result1 = (px * qy) + (py * xx) + (xy * qx)
			- ((px * xy) + (py * qx) + (qy * xx));

//	result2 = (px * xy) + (py * qx) + (qy * xx);



	result = result1;

	if (result > 0) {
		result_f = 1;
	} else if (result < 0) {
		result_f = -1;
	} else if (result == 0) {
		result_f = 0;
	}

	return result_f;

}

int orientation(int *a, int *b, int *e, int *c, int *points) {

	int result1 = 0;
	int result3 = 0;
	int result4 = 0;

	int result = 0;

	result1 = or_test(a, b, c, points);
	result3 = or_test(b, e, c, points);

//	result2 = or_test(b, e, c, points);
	result4 = or_test(e, a, c, points);

	if(step==14){
		if(*a==54097 && *b==54994 && *e==56788){
			printf("a %d,b %d,e %d,c %d\n",*a,*b,*e,*c);
			printf("result1 %d, result3 %d, result4 %d\n",result1,result3,result4);
		}
	}

	if ((result1 == result3) && (result3==result4)) {
		result = 1;
	} else if (result1 == 0 || result4 == 0 || result3 == 0) {

		if (result3 == 0) {
			if (result1 == result4) {
				result = 1;
			} else {
				result = 0;
			}
			//printf("result1,result3,result4 %d,%d,%d = %d\n",result1,result3,result4,result);
		} else if (result1 == 0) {

			if (result3 == result4) {
				result = 1;
				printf("result1,result3,result4 %d,%d,%d = %d\n",result1,result3,result4,result);
			} else {
				result = 0;
			}
		} else if (result4 == 0) {
			if (result1 == result3) {
				result = 1;
			} else {
				result = 0;
			}
			//printf("result1,result3,result4 %d,%d,%d = %d\n",result1,result3,result4,result);
		}

	} else {
		result = 0;
		//printf("result1,result3,result4 %d,%d,%d = %d\n",result1,result3,result4,result);
	}

	return result;

}

int *triangle3(int *points, int *a, int *b, int *z, int *new_triangles,
		int num_of_prev_tri, int *previous_tri) {


	if(step==14){

		if(*a==54994 || *b==54994 || *z==54994){
			printf("In 3------------->, %d,%d,%d\n",*a,*b,*z);
		}

	}


	int num = 0;

	new_triangles[new_index] = *a;
	new_index++;
	new_triangles[new_index] = *b;
	new_index++;
	new_triangles[new_index] = *z;
	new_index++;

	new_triangles[new_index] = num_of_prev_tri;
	new_index++;

	re_tri++;

	num = 0;
	while (num < num_of_prev_tri) {

		new_triangles[new_index] = previous_tri[num];
		num++;
		new_index++;

	}

	new_index = new_index + (6 - num);

/*
	if(step==14){
	printf("re tri in3 is %d\n",re_tri);
	}
*/


	return new_triangles;

}

int *triangle4(int *points, int *b, int *c, int *d, int *e, int *new_triangles,
		int num_of_prev_tri, int *previous_tri) {

	int result = 0;
	int num = 0;
	result = orientation(b, e, d, c, points);

	int temp_index;

/*
	if(step==14){
	printf("entered triangle4\n");
	printf("result is, re tri--->%d, %d\n",result,re_tri);
	}
*/


	if (result == 1) {

		temp_index = new_index;

		if(step==14){

			if(*c==54994 || *b==54994 || *e==54994){
				printf("In4(1)------------->, b %d,c %d,d %d,e %d,new_index %d\n",*b,*c,*d,*e,new_index);
			}

		}

		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *c;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		temp_index = new_index;

		if(step==14){

			if(*c==54994 || *d==54994 || *e==54994){
				printf("In4(2)------------->, b %d,c %d,d %d,e %d,new_index %d\n",*b,*c,*d,*e,new_index);
			}

		}

		new_triangles[new_index] = *c;
		new_index++;
		new_triangles[new_index] = *d;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

	} else if (result == 0) {


		temp_index = new_index;

		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;
		new_triangles[new_index] = *d;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		if(step==14){

			if(*d==54994 || *b==54994 || *e==54994){
				printf("In4(3)------------->, b %d,c %d,d %d,e %d,new_index %d\n",*b,*c,*d,*e,new_index);

				printf("b point %d,%d\n",points[(*b) * 2],points[((*b) * 2) + 1]);
				printf("c point %d,%d\n",points[(*c) * 2],points[((*c) * 2) + 1]);
				printf("d point %d,%d\n",points[(*d) * 2],points[((*d) * 2) + 1]);
				printf("e point %d,%d\n",points[(*e) * 2],points[((*e) * 2) + 1]);



			}

		}


		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		temp_index = new_index;

		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *c;
		new_index++;
		new_triangles[new_index] = *d;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		if(step==14){

			if(*c==54994 || *b==54994 || *d==54994){
				printf("In4(4)------------->, b %d,c %d,d %d,e %d,new_index %d\n",*b,*c,*d,*e,new_index);
			}

		}



		re_tri++;

/*
		if(step==14){
		printf("re tri is---- %d\n",re_tri);
		}
*/


		if (step == 4) {
			//printf("c is outside complete 2\n");
		}

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

	}

/*
	if(step==14){
	printf("re tri in 4 is %d\n",re_tri);
	}
*/


	return new_triangles;
}

int *triangle5(int *points, int *a, int *b, int *c, int *d, int *e,
		int *new_triangles, int num_of_prev_tri, int *previous_tri) {

/*
	if(step==14){
	printf("entered triangle5\n");
	}
*/

	int temp_index;

	int result = 0;
	int num = 0;
	int result_c = 0;
	int result_d = 0;

	result = orientation(a, b, e, c, points);

	if (result == 1) {
		//printf("c is inside\n");
		result_c = 1;

	} else if (result == 0) {
		//printf("c is outside\n");
		result_c = 0;

	}

	result = orientation(a, b, e, d, points);

	if (result == 1) {

		//printf("d is inside\n");
		result_d = 1;
	} else if (result == 0) {

		//printf("result_d is 0\n");

		//printf("d is outside\n");
		result_d = 0;
	}

	if (result_c == 0 && result_d == 0) {
		// form triangle abe and send b,c,d,e to triangle4()

		if (step == 4) {
			//printf("result_c0 and result_d0 \n");
		}

		temp_index = new_index;

		if(step==14){

			if(*a==54994 || *b==54994 || *e==54994){
				printf("In 5------------->, %d,%d,%d\n",*a,*b,*e);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		new_triangles = triangle4(points, b, c, d, e, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 1 && result_d == 0) {

		if(step==14){

			if(*a==54994 || *b==54994 || *c==54994){
				printf("In 5------------->, %d,%d,%d\n",*a,*b,*c);
			}

		}

		temp_index = new_index;
		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *c;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		new_triangles = triangle4(points, a, c, d, e, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 0 && result_d == 1) {

		if (step == 4) {
			//printf("result_c0 and result_d1 \n");
		}

		temp_index = new_index;

		if(step==14){

			if(*a==54994 || *d==54994 || *e==54994){
				printf("In 5------------->, %d,%d,%d\n",*a,*d,*e);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *d;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		new_triangles = triangle4(points, a, b, c, d, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 1 && result_d == 1) {

		int cx = points[(*c) * 2];
		int dx = points[(*d) * 2];

		if (step == 4) {
			//printf("result_c1 and result_d1 \n");
		}

		if (cx < dx) {

			temp_index = new_index;

			if(step==14){

				if(*a==54994 || *b==54994 || *c==54994){
					printf("In 5------------->, %d,%d,%d\n",*a,*b,*c);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *b;
			new_index++;
			new_triangles[new_index] = *c;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle4(points, a, c, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (cx > dx) {

			temp_index = new_index;

			if(step==14){

				if(*a==54994 || *d==54994 || *e==54994){
					printf("In 5------------->, %d,%d,%d\n",*a,*d,*e);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *d;
			new_index++;
			new_triangles[new_index] = *e;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle4(points, a, b, c, d, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (cx == dx) {

			temp_index = new_index;

			if(step==14){

				if(*a==54994 || *b==54994 || *c==54994){
					printf("In 5------------->, %d,%d,%d\n",*a,*b,*c);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *b;
			new_index++;
			new_triangles[new_index] = *c;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle4(points, a, c, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

		}

	}

/*
	if(step==14){
	printf("re tri in 5 is %d\n",re_tri);
	}
*/


	return new_triangles;
}

int *triangle6(int *points, int *a, int *b, int *c, int *d, int *e, int *f,
		int *new_triangles, int num_of_prev_tri, int *previous_tri) {

	int temp_index;

	int result = 0;
	int num = 0;
	int result_c = 0;
	int result_d = 0;
	int result_e = 0;

	result = orientation(a, b, f, c, points);

	if (result == 1) {
		//printf("c is inside\n");

		result_c = 1;
	} else if (result == 0) {
		//printf("c is outside\n");

		result_c = 0;

	}

	result = orientation(a, b, f, d, points);

	if (result == 1) {
		//printf("d is inside\n");

		result_d = 1;
	} else if (result == 0) {
		//printf("d is outside\n");

		result_d = 0;
	}

	result = orientation(a, b, f, e, points);

	if (result == 1) {
		//printf("e is inside\n");

		result_e = 1;
	} else if (result == 0) {
		//printf("e is outside\n");

		result_e = 0;
	}

/*
	if(step==14){
	printf("entered triangle6\n");
	//printf("c %d, d %d ,e %d\n",result_c,result_d,result_e);
	}
*/


	if(result_c == 1 && result_d == 1 && result_e == 1){

		int cx = points[(*c) * 2];
		int dx = points[(*d) * 2];
		int ex = points[(*e) * 2];

		if (cx<=dx && cx<=ex) {

			temp_index = new_index;

			if(step==14){

				if(*a==54994 || *b==54994 || *c==54994){
					printf("In 6------------->, %d,%d,%d\n",*a,*b,*c);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *b;
			new_index++;
			new_triangles[new_index] = *c;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle5(points, a, c, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		}else if (dx<=cx && dx<=ex) {

			new_triangles = triangle4(points, a, b, c, d, new_triangles,
					num_of_prev_tri, previous_tri);

			new_triangles = triangle4(points, a, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		}else if(ex<=cx && ex<=dx){

			temp_index = new_index;

			if(step==14){

				if(*a==54994 || *f==54994 || *e==54994){
					printf("In 6------------->, %d,%d,%d\n",*a,*f,*e);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *e;
			new_index++;
			new_triangles[new_index] = *f;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle5(points, a, b, c, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

		}

	}else if (result_c == 0 && result_d == 0 && result_e == 0) {

		// c,d,e are all outside so form abf triangle and send bcdef to triangle 5

		temp_index = new_index;
		if(step==14){

			if(*a==54994 || *b==54994 || *f==54994){
				printf("In 6------------->, %d,%d,%d\n",*a,*b,*f);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *f;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		new_triangles = triangle5(points, b, c, d, e, f, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 1 && result_d == 0 && result_e == 0) {

		temp_index = new_index;
		if(step==14){

			if(*a==54994 || *b==54994 || *c==54994){
				printf("In 6------------->, %d,%d,%d\n",*a,*b,*c);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *c;
		new_index++;
		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		/*
		 temp_index = new_index;

		 new_triangles[new_index] = *a;
		 new_index++;
		 new_triangles[new_index] = *c;
		 new_index++;
		 new_triangles[new_index] = *f;
		 new_index++;

		 new_triangles[new_index] = num_of_prev_tri;
		 new_index++;



		 re_tri++;

		 num = 0;
		 while (num < num_of_prev_tri) {

		 new_triangles[new_index] = previous_tri[num];
		 num++;
		 new_index++;

		 }
		 new_index = new_index + (6 - num);
		 */

		new_triangles = triangle5(points, a, c, d, e, f, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 0 && result_d == 1 && result_e == 0) {

		new_triangles = triangle4(points, a, b, c, d, new_triangles,
				num_of_prev_tri, previous_tri);

		new_triangles = triangle4(points, a, d, e, f, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 0 && result_d == 0 && result_e == 1) {

		temp_index = new_index;
		if(step==14){

			if(*a==54994 || *e==54994 || *f==54994){
				printf("In 6------------->, %d,%d,%d\n",*a,*e,*f);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *e;
		new_index++;
		new_triangles[new_index] = *f;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		new_triangles = triangle5(points, a, b, c, d, e, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 1 && result_d == 1 && result_e == 0) {

		int cx = points[(*c) * 2];
		int dx = points[(*d) * 2];

		if (cx < dx) {

			temp_index = new_index;
			if(step==14){

				if(*a==54994 || *b==54994 || *c==54994){
					printf("In 6------------->, %d,%d,%d\n",*a,*b,*c);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *b;
			new_index++;
			new_triangles[new_index] = *c;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle5(points, a, c, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (cx > dx) {

			new_triangles = triangle4(points, a, b, c, d, new_triangles,
					num_of_prev_tri, previous_tri);

			new_triangles = triangle4(points, a, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (cx == dx) {

			temp_index = new_index;
			if(step==14){

				if(*a==54994 || *b==54994 || *c==54994){
					printf("In 6------------->, %d,%d,%d\n",*a,*b,*c);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *b;
			new_index++;
			new_triangles[new_index] = *c;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle5(points, a, c, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		}

	} else if (result_c == 1 && result_d == 0 && result_e == 1) {

		temp_index = new_index;
		if(step==14){

			if(*a==54994 || *b==54994 || *c==54994){
				printf("In 6------------->, %d,%d,%d\n",*a,*b,*c);
			}

		}

		new_triangles[new_index] = *a;
		new_index++;
		new_triangles[new_index] = *b;
		new_index++;
		new_triangles[new_index] = *c;
		new_index++;

		new_triangles[new_index] = num_of_prev_tri;
		new_index++;

		re_tri++;

		num = 0;
		while (num < num_of_prev_tri) {

			new_triangles[new_index] = previous_tri[num];
			num++;
			new_index++;

		}
		new_index = new_index + (6 - num);

		/*
		 temp_index = new_index;

		 new_triangles[new_index] = *a;
		 new_index++;
		 new_triangles[new_index] = *e;
		 new_index++;
		 new_triangles[new_index] = *f;
		 new_index++;
		 new_triangles[new_index] = num_of_prev_tri;
		 new_index++;



		 re_tri++;

		 num = 0;
		 while (num < num_of_prev_tri) {

		 new_triangles[new_index] = previous_tri[num];
		 num++;
		 new_index++;

		 }
		 new_index = new_index + (6 - num);
		 */

		new_triangles = triangle5(points, a, c, d, e, f, new_triangles,
				num_of_prev_tri, previous_tri);

	} else if (result_c == 0 && result_d == 1 && result_e == 1) {

		int dx = points[(*c) * 2];
		int ex = points[(*e) * 2];

		if (dx < ex) {

			new_triangles = triangle4(points, a, b, c, d, new_triangles,
					num_of_prev_tri, previous_tri);

			new_triangles = triangle4(points, a, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (dx > ex) {

			temp_index = new_index;
			if(step==14){

				if(*a==54994 || *e==54994 || *f==54994){
					printf("In 6------------->, %d,%d,%d\n",*a,*e,*f);
				}

			}

			new_triangles[new_index] = *a;
			new_index++;
			new_triangles[new_index] = *e;
			new_index++;
			new_triangles[new_index] = *f;
			new_index++;

			new_triangles[new_index] = num_of_prev_tri;
			new_index++;

			re_tri++;

			num = 0;
			while (num < num_of_prev_tri) {

				new_triangles[new_index] = previous_tri[num];
				num++;
				new_index++;

			}
			new_index = new_index + (6 - num);

			new_triangles = triangle5(points, a, b, c, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (dx == ex) {

			new_triangles = triangle4(points, a, b, c, d, new_triangles,
					num_of_prev_tri, previous_tri);

			new_triangles = triangle4(points, a, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		}

	}

/*
	if(step==14){
	printf("re tri in 6 is %d\n",re_tri);
	}
*/

	return new_triangles;

}

int *find_A(int vcount, int *a, int *vertex, int set, int *points) {

	int first = 0;
	int f = 0;
	int min = 0;
	int max_y = 0;

	while (f < vcount) {

		//printf("%d ,", vertex[f]);
		if (first == 0 && vertex[f] != set) {
			min = points[(vertex[f]) * 2];
			max_y = points[((vertex[f]) * 2) + 1];
			*a = vertex[f];
			first++;
		}



/*
		if ((points[(vertex[f]) * 2] <= min) && vertex[f] != set) {

			if (points[(vertex[f]) * 2] == min) {

				if (max_y > points[((vertex[f]) * 2) + 1]) {

				} else if (max_y < points[((vertex[f]) * 2) + 1]) {
					min = points[(vertex[f]) * 2];
					max_y = points[((vertex[f]) * 2) + 1];
					*a = vertex[f];
				}

			} else if (points[(vertex[f]) * 2] < min) {
				min = points[(vertex[f]) * 2];
				max_y = points[((vertex[f]) * 2) + 1];
				*a = vertex[f];
			}

		}
*/




		if ((points[(vertex[f]) * 2] < min) && vertex[f] != set) {
				min = points[(vertex[f]) * 2];
				max_y = points[((vertex[f]) * 2) + 1];
				*a = vertex[f];
		}



		f++;
	}

	return a;
}

int *find_B(int vcount, int *b, int *a, int *vertex, int set, int *points) {

	int f = 0;

	f = 0;
	while (f < vcount) {

		if (vertex[f] == *a) {

			if (f % 3 == 0) {

				if (vertex[f + 1] == set) {
					*b = vertex[f + 2];
				} else if (vertex[f + 2] == set) {
					*b = vertex[f + 1];
				}

			} else if (f % 3 == 1) {

				if (vertex[f - 1] == set) {
					*b = vertex[f + 1];
				} else if (vertex[f + 1] == set) {
					*b = vertex[f - 1];
				}
			}

			else if (f % 3 == 2) {

				if (vertex[f - 1] == set) {
					*b = vertex[f - 2];
				} else if (vertex[f - 2] == set) {
					*b = vertex[f - 1];
				}
			}
		}

		f++;
	}

	return b;

}

int *find_vertex(int vcount, int *z, int *b, int *min_vertex, int *vertex,
		int set, int *points) {

	int f = 0;
	while (f < vcount) {

		if (vertex[f] == *b) {

			if (f % 3 == 0) {

				if ((vertex[f + 1] == set && vertex[f + 2] == *min_vertex)
						|| (vertex[f + 2] == set && vertex[f + 1] == *min_vertex)) {
					//b = vertex[f + 2];

				} else if (vertex[f + 2] == set
						|| vertex[f + 2] == *min_vertex) {
					*z = vertex[f + 1];
				} else if (vertex[f + 1] == set
						|| vertex[f + 1] == *min_vertex) {
					*z = vertex[f + 2];
				}

			} else if (f % 3 == 1) {

				if ((vertex[f - 1] == set && vertex[f + 1] == *min_vertex)
						|| (vertex[f + 1] == set && vertex[f - 1] == *min_vertex)) {
					//b = vertex[f + 1];
				} else if (vertex[f + 1] == set
						|| vertex[f + 1] == *min_vertex) {
					*z = vertex[f - 1];
				} else if (vertex[f - 1] == set
						|| vertex[f - 1] == *min_vertex) {
					*z = vertex[f + 1];
				}
			}

			else if (f % 3 == 2) {

				if ((vertex[f - 1] == set && vertex[f - 2] == *min_vertex)
						|| (vertex[f - 2] == set && vertex[f - 1] == *min_vertex)) {
					//b = vertex[f - 2];
				} else if (vertex[f - 2] == set
						|| vertex[f - 2] == *min_vertex) {
					*z = vertex[f - 1];
				} else if (vertex[f - 1] == set
						|| vertex[f - 1] == *min_vertex) {
					*z = vertex[f - 2];
				}
			}
		}

		f++;
	}

	return z;
}

int *Retriangulation(int num_of_points, int *new_triangles, int n, int start,
		int end, int *points) {

	int k = 0;

	step++;
	printf("iteration number %d\n", step);
	int *degree = (int *) calloc(n, sizeof(int));

	num_of_points = end - start;
	printf("start is %d\n", start);
	printf("end is %d\n", end);
	printf("calculated number of points %d\n", num_of_points);

	int *temp_new_tri = new_triangles + (start * 10);

	int degree_with_2 = 0;

	k = start;
	while (k < end) {

		degree[*temp_new_tri]++;
		degree[*(temp_new_tri + 1)]++;
		degree[*(temp_new_tri + 2)]++;

		temp_new_tri = temp_new_tri + 10;
		k++;
	}

	int *set = (int *) calloc(n * 10, sizeof(int));
	int *temp = degree;

	k = 0;
	int j = 0;
	while (k < n) {

		//printf("at %d, degree is %d,n is %d\n", k, temp[k],n);
		set[j] = k;
		set[j + 1] = temp[k];
		set[j + 3] = temp[k];
		j = j + 10;
		k++;
	}

	int p = 0;

//	printf("j valus is %d\n", j);

	printf("check degree greater than 6 in step %d\n", step);
	while (p < j) {

		if (set[p + 1] > 10) {
			printf("at %d,point %d, degree is %d\n", p, set[p], set[p + 1]);

		}

		if(set[p]==90000 || set[p]==90001 || set[p]==90002){

			printf("Inside at %d,point %d, degree is %d\n", p, set[p], set[p + 1]);
		}

		p = p + 10;

	}

	k = 0;

	int index = start * 10;
//	printf("index before entering create table %d\n", index);

	k = 0;
	int *temp_tri = new_triangles + (start * 10);
	p = 0;
	int deg = 0;
	int tri_index = 0;
	while (k < num_of_points) {
		int temp_index = index;


		p = *temp_tri * 10;
		//printf("point index is %d, %d\n",p,set[p]);

		deg = set[p + 3];

		if (set[p + 1] <= 6 && set[p + 1] != 0) {

			/*
			 if(step==3){
			 printf("point index is %d,point is %d,index is %d\n",p,set[p],index);
			 }
			 */

			if (deg == set[p + 1]) {
				if (index % 10 == 0) {
					set[p + 4] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 4]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 4] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 4]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 4] = index;
					if (k < 10) {
						//printf("index------------- %d\n",set[p + 4]);
					}

				}

			} else if (set[p + 1] - deg == 1) {
				if (index % 10 == 0) {
					set[p + 5] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 5]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 5] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 5]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 5] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 5]);
					}

				}

			} else if (set[p + 1] - deg == 2) {
				if (index % 10 == 0) {
					set[p + 6] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 6]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 6] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 6]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 6] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 6]);
					}

				}

			} else if (set[p + 1] - deg == 3) {
				if (index % 10 == 0) {
					set[p + 7] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 7]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 7] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 7]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 7] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 7]);
					}

				}

			} else if (set[p + 1] - deg == 4) {
				if (index % 10 == 0) {
					set[p + 8] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 8]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 8] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 8]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 8] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 8]);
					}

				}

			} else if (set[p + 1] - deg == 5) {
				if (index % 10 == 0) {
					set[p + 9] = index / 10;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 9]);
					}

				} else if (index % 10 == 1) {
					index = (index - 1) / 10;
					set[p + 9] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 9]);
					}

				} else if (index % 10 == 2) {
					index = (index - 2) / 10;
					set[p + 9] = index;
					if (k < 10) {
						//printf("index------------ %d\n",set[p + 9]);
					}

				}

			}

		} else {
			//printf("caught invalid is %d, %d\n",p,set[p]);
			set[p + 2] = 0;
		}

		deg--;
		set[p + 3] = deg;

		if (tri_index == 2) {
			tri_index = 0;

			index = temp_index;
			index = index + 8;
			temp_tri = temp_tri + 8;
			k++;

		} else if (tri_index < 2) {
			tri_index++;
			temp_tri++;

			index = temp_index;
			index++;

		}

	}

	printf("table created\n");



	 if (step == 14) {
	 p = 0;
	 while (p < j) {
	 if (set[p] == 54994) {

	 printf(
	 "at %d,point %d, degree is %d,valid %d,degree %d,(%d,%d,%d,%d,%d,%d)\n",
	 p, set[p], set[p + 1], set[p + 2], set[p + 3],
	 set[p + 4], set[p + 5], set[p + 6], set[p + 7],
	 set[p + 8], set[p + 9]);

	 }
	 p = p + 10;
	 }
	 }



	int *f_t = (int *) malloc(n * 6 * sizeof(int));
	p = 0;
	int c = 0;
	int tri = 0;
	int v = 0;
	int check = 0;
	int flag = 0;
	while (p < j) {

		if (set[p] == 90000 || set[p] == 90001 || set[p] == 90002) {

			//printf("90000 or 90001 or 90002 %d at p %d\n", set[p], p);
			// make 0 ,1 and 2 invalid and add associated triangles to f_T
			set[p + 2] = 0;

		} else {

			if (set[p + 1] <= 6 && set[p + 1] != 0) {

				check = 0;
				tri = set[p + 1];
				v = p + 4;
				flag = 0;
				while (tri != 0) {

					check = 0;
					while (check < c) {
						if (f_t[check] == set[v]) {
							flag = 1;

							//printf("caught %d\n",set[p]);
							break;
						}
						check++;

					}
					if (flag == 1) {
						break;
					}

					v++;
					tri--;
				}

				if (flag == 1) {

					set[p + 2] = 0;
				} else if (flag == 0) {
					tri = set[p + 1];
					v = p + 4;
					while (tri != 0) {

						f_t[c] = set[v];
						tri--;
						v++;
						c++;
					}
					set[p + 2] = 1;
				}

			} else {
				set[p + 2] = 0;
			}

		}

		p = p + 10;

	}

	printf("validation done\n");

	p = 0;
	while (p < j) {

		/*
		 if (set[p + 4] == 44573 || set[p + 5] == 44573 || set[p + 6] == 44573
		 || set[p + 7] == 44573 || set[p + 8] == 44573
		 || set[p + 9] == 44573) {

		 printf(
		 "at %d,point %d, degree is %d,valid %d,(%d,%d,%d,%d,%d,%d)\n",
		 p, set[p], set[p + 1], set[p + 2], set[p + 4], set[p + 5],
		 set[p + 6], set[p + 7], set[p + 8], set[p + 9]);

		 }
		 */

		p = p + 10;

	}

	if(step==14){
	 printf("440582 has %d,%d,%d\n",new_triangles[4405820],new_triangles[4405821],new_triangles[4405822]);
	 printf("441509 has %d,%d,%d\n",new_triangles[4415090],new_triangles[4415091],new_triangles[4415092]);
	 printf("441531 has %d,%d,%d\n",new_triangles[4415310],new_triangles[4415311],new_triangles[4415312]);
	}

	p = 0;
	int *valid1 = (int *) malloc(270009 * sizeof(int));
	int v1 = 0;
	int check1 = 0;
	int degree5 = 0;
	int degree6 = 0;
	int degree4 = 0;
	int degree3 = 0;
	int degree1 = 0;
	int degree2 = 0;

	while (p < j) {

		int count = 0;
		int flag = 0;
		int degree = set[p + 1];
		v = p + 4;
		if (set[p + 2] == 1) {
			check1++;
			if (degree == 3) {
				degree3++;
			} else if (degree == 2) {
				degree2++;
			} else if (degree == 1) {
				degree1++;
			} else if (degree == 4) {
				degree4++;
			} else if (degree == 5) {
				degree5++;
			} else if (degree == 6) {
				degree6++;
			}

			while (degree > 0) {

				flag = 0;
				count = 0;
				while (count < v1) {
					if (valid1[count] == set[v]) {
						printf("something is wrong...........\n");
						flag = 1;
						break;
					}
					count++;
				}

				if (flag == 0) {
					valid1[v1] = set[v];
					v1++;
				} else if (flag == 1) {

				}

				v++;
				degree--;

			}

		}

		p = p + 10;

	}

	printf("number of vertex selected %d\n", check1);

	printf(" degree with 1 %d\n", degree1);
	printf(" degree with 2 %d\n", degree2);
	printf(" degree with 3 %d\n", degree3);
	printf(" degree with 4 %d\n", degree4);
	printf(" degree with 5 %d\n", degree5);
	printf(" degree with 6 %d\n", degree6);

	int to_be_removed = 0;
	while (to_be_removed < v1) {
		//printf("caught valid %d\n", valid1[to_be_removed]);
		to_be_removed++;
	}

	//printf("v1 valud is %d\n",v1);
	//printf("triangles to be removed are %d\n", to_be_removed);
	//printf("\n");

	int new_tri_count = num_of_points - to_be_removed;
	int triangles_copied = new_tri_count;

	temp_tri = new_triangles + (start * 10);

	degree_with_2 = 0;

	k = start;
	index = end;

/*
	printf("k vlaue-----%d\n", k);
	printf("num of points ........ %d\n", num_of_points);
*/

	while (k < end) {

		flag = 0;
		p = 0;
		while (p < v1) {
			if (valid1[p] == k) {

				flag = 1;

				break;
			}
			p++;
		}

		if (flag == 0) {

			//printf("inside index..... step 3\n");
			if(step==14){

				if(*temp_tri==54994 || *(temp_tri + 1)==54994 || *(temp_tri + 2)==54994){
					printf("In 5------------->, %d,%d,%d,new index is %d\n",*temp_tri,*(temp_tri + 1),*(temp_tri + 2),new_index);
				}

			}


			new_triangles[new_index] = *temp_tri;
			new_index++;
			new_triangles[new_index] = *(temp_tri + 1);
			new_index++;
			new_triangles[new_index] = *(temp_tri + 2);
			new_index++;
			new_triangles[new_index] = 1;
			new_index++;
			new_triangles[new_index] = k;
			new_index = new_index + 6;
			index++;

		} else if (flag == 1) {

		}

		temp_tri = temp_tri + 10;
		k++;
	}

//	printf("end %d, new triangle index %d\n", end, index);
	index = index - end;

	printf("new formed triangle should have count as %d\n", new_tri_count);
	printf("new formed triangles before re triangulation is %d\n", index);

	re_tri = 0;
	printf("start triangulation in step %d\n", step);

//	int *vertex = (int *) malloc(18 * sizeof(int));
	int vcount = 0;
	p = 0;
	int *z = (int *) calloc(sizeof(int), 1);
	int *b = (int *) calloc(sizeof(int), 1);
	int *d = (int *) calloc(sizeof(int), 1);
	int *e = (int *) calloc(sizeof(int), 1);
	int *a = (int *) calloc(sizeof(int), 1);
	int *f = (int *) calloc(sizeof(int), 1);

	int t1 = 0;
	int t2 = 0;

	int degree_valid = 0;
	//new_triangles = new_triangles + start;
	temp_tri = new_triangles;

	int *previous_tri = (int *) calloc(sizeof(int), 6);
	int num_of_prev_tri = 0;
	int num = 0;

	int check3 = 0;
	int check4 = 0;
	int check5 = 0;
	int check6 = 0;

	while (p < j) {

		int *vertex = (int *) malloc(18 * sizeof(int));
		int t = 0;
		num_of_prev_tri = set[p + 1];
		if (set[p + 2] == 1 && set[p + 1] == 3) {

			if (step == 4) {
				//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			}
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 10];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 1];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 2];
				vcount++;
				degree_valid--;
				v++;
			}
			if (step == 4) {
				check3++;
				//printf("points colleted , degree 3, check %d\n",check3);
			}
			//printf("\n");
			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			//printf("find_a is %d, ", *a);

			b = find_B(vcount, b, a, vertex, set[p], points);
			//printf("b is %d, ", *b);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			//printf("z is %d, ", *z);

			new_triangles = triangle3(points, a, b, z, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (set[p + 2] == 1 && set[p + 1] == 2) {

				printf("caught with degree 2 %d, degree is----> %d\n", set[p],
			 set[p + 1]);

		} else if (set[p + 2] == 1 && set[p + 1] == 4) {

			if (step == 4) {
				//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			}
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;
				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 10];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 1];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 2];
				vcount++;
				degree_valid--;
				v++;
			}
			if (step == 4) {
				check4++;
				//printf("points colleted , degree 4,check %d\n",check4);
			}

			//printf("\n");
			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			/*
			 if(*a==1500){
			 printf("a is %d, step %d, 4\n",*a,step);
			 }
			 */

			b = find_B(vcount, b, a, vertex, set[p], points);
			/*
			 if(*b==1500){
			 printf("b is %d, step %d\n",*b,step);
			 }
			 */

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			/*
			 if(*z==1500){
			 printf("c is %d, step %d\n",*z,step);
			 }
			 */

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			/*
			 if(*d==1500){
			 printf("d is %d, step %d\n",*d,step);
			 }
			 */
			if(step==14){

				if(*a==54097 || *b==54362 || *z==56788 || *d==54994){
					printf("In4(3)---set %d---------->, b %d,c %d,d %d,e %d,new_index %d\n",set[p],*a,*b,*z,*d,new_index);

				}

			}
			new_triangles = triangle4(points, a, b, z, d, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (set[p + 2] == 1 && set[p + 1] == 5) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			if (step == 4) {
				//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			}
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 10];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 1];
				vcount++;
				vertex[vcount] = temp_tri[(t * 10) + 2];
				vcount++;
				degree_valid--;
				v++;
			}
			if (step == 4) {
				check5++;
				//printf("points colleted , degree 5,check %d\n",check5);
			}

			//printf("\n");
			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			/*
			 if(*a==1500){
			 printf("a is %d, step %d , 5\n",*a, step);
			 }
			 */

			b = find_B(vcount, b, a, vertex, set[p], points);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			/*
			 if(*z==1500){
			 printf("c is %d, step %d, 5\n",*z, step);
			 }
			 */

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			/*
			 if(*d==1500){
			 printf("d is %d, step %d, 5\n",*d, step);
			 }
			 */

			e = find_vertex(vcount, e, d, z, vertex, set[p], points);
			/*
			 if(*e==1500){
			 printf("e is %d, step %d, 5\n",*e, step);
			 }
			 */

			new_triangles = triangle5(points, a, b, z, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

		} else if (set[p + 2] == 1 && set[p + 1] == 6) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			if (step == 4) {
				//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			}
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 10];
				vcount++;

				vertex[vcount] = temp_tri[(t * 10) + 1];
				vcount++;

				vertex[vcount] = temp_tri[(t * 10) + 2];
				vcount++;

				degree_valid--;
				v++;
			}
			if (step == 6) {
				check6++;
				//printf("points colleted , degree 6,check %d\n",check6);
			}

			a = find_A(vcount, a, vertex, set[p], points);

			/*
			 if(*a==1500){
			 printf("a is %d, step %d, 6\n",*a, step);
			 }
			 */

			b = find_B(vcount, b, a, vertex, set[p], points);
			/*
			 if(*b==1500){
			 printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			 printf("b is %d, step %d, 6\n",*b, step);
			 }
			 */

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			/*
			 if(*z==1500){
			 printf("c is %d, step %d, 6\n",*z, step);
			 }
			 */

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			/*
			 if(*d==1500){
			 printf("d is %d, step %d, 6\n",*d, step);
			 }
			 */

			e = find_vertex(vcount, e, d, z, vertex, set[p], points);
			/*			if(*e==1500){

			 printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			 printf("e is %d, step %d, 6\n",*e, step);
			 }
			 */

			f = find_vertex(vcount, f, e, d, vertex, set[p], points);

			//printf("points calculation done in 6\n");
			new_triangles = triangle6(points, a, b, z, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

		}

		p = p + 10;

	}

	printf("re_tri , number tri retriagulated %d\n", re_tri);

	printf("new index after retriangulation is %d\n", new_index);
	p = start * 10;
	index = start;
	while (p < new_index) {

		/*
		 if(new_triangles[p]==1500 || new_triangles[p + 1]==1500 || new_triangles[p + 2]==1500){
		 //printf("at p %d, %d, %d, %d\n", index, new_triangles[p],new_triangles[p + 1], new_triangles[p + 2]);
		 }
		 if(step==2){
		 printf("at p %d, %d, %d, %d\n", index, new_triangles[p],new_triangles[p + 1], new_triangles[p + 2]);
		 }
		 */
		p = p + 10;
		index++;
	}

	new_tri_count = new_tri_count + end;
	new_tri_count = index - new_tri_count;

	printf("new index is %d and p %d should match\n", new_index, p);
	printf("total number of triangles till now %d\n", index);
	num_of_points = index;
	printf("triangles added after re triangulation %d\n", new_tri_count);

	new_tri_count = new_tri_count + triangles_copied;

	printf("total number of new triangles in this iteration %d\n",
			new_tri_count);

	t1 = 0;
	t2 = 0;
	t1 = ts;
	tri_start[ts] = end;
	ts++;
	t2 = ts;
	tri_start[ts] = num_of_points;
	ts++;

	if (step < 28) {
		new_triangles = Retriangulation(num_of_points, new_triangles, n,
				tri_start[t1], tri_start[t2], points);
	}

	return new_triangles;
}

int *find_degree(int *points, int *triangles, int m, int n) {

	int *temp_tri = triangles;
	int *point = points;
	int *degree = (int *) calloc(n, sizeof(int));

	step++;
	printf("iteration number %d\n", step);
	int k = 0;

	/*
	 while (k < n) {

	 printf("at point k %d, ( %d , %d)\n", k, *point, *(point + 1));
	 point = point + 2;
	 k++;
	 }
	 */

	k = 0;
	while (k < m) {

		degree[*temp_tri]++;
		degree[*(temp_tri + 1)]++;
		degree[*(temp_tri + 2)]++;

		temp_tri = temp_tri + 3;
		k++;
	}

	int *temp = degree;

	int *set = (int *) calloc(n * 10, sizeof(int));

	k = 0;
	int j = 0;
	while (k < n) {

		//printf("at %d, degree is %d\n", k, temp[k]);
		set[j] = k;
		set[j + 1] = temp[k];
		set[j + 3] = temp[k];
		j = j + 10;
		k++;
	}

	int p = 0;

//	printf("j valus is %d\n", j);

	/*
	 while (p < j) {
	 printf("at %d,point %d, degree is %d\n", p, set[p], set[p + 1]);
	 p = p + 10;

	 }
	 */

	k = 0;

	int index = 0;
	temp_tri = triangles;
	int deg = 0;
	while (k < m * 3) {
		p = 0;
		p = *temp_tri * 10;
		deg = set[p + 3];

		if (set[p + 1] <= 6) {

			if (deg == set[p + 1]) {
				if (index % 3 == 0) {
					set[p + 4] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 4] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 4] = index / 3;
				}

			} else if (set[p + 1] - deg == 1) {
				if (index % 3 == 0) {
					set[p + 5] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 5] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 5] = index / 3;
				}

			} else if (set[p + 1] - deg == 2) {
				if (index % 3 == 0) {
					set[p + 6] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 6] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 6] = index / 3;
				}

			} else if (set[p + 1] - deg == 3) {
				if (index % 3 == 0) {
					set[p + 7] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 7] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 7] = index / 3;
				}

			} else if (set[p + 1] - deg == 4) {
				if (index % 3 == 0) {
					set[p + 8] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 8] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 8] = index / 3;
				}

			} else if (set[p + 1] - deg == 5) {
				if (index % 3 == 0) {
					set[p + 9] = index / 3;
				} else if (index % 3 == 1) {
					index = index - 1;
					set[p + 9] = index / 3;
				} else if (index % 3 == 2) {
					index = index - 2;
					set[p + 9] = index / 3;
				}

			}

		} else {
			set[p + 2] = 0;
		}

		deg--;
		set[p + 3] = deg;
		temp_tri++;
		index = k;
		index++;
		k++;

	}

	printf("table created\n");

	int *f_t = (int *) malloc(n * 6 * sizeof(int));
	p = 0;
	int c = 0;
	int tri = 0;
	int v = 0;
	int check = 0;
	int flag = 0;
	while (p < j) {

		if (set[p] == 90000 || set[p] == 90001 || set[p] == 90002) {

			//printf("90000 or 90001 or 90002 %d at p %d\n", set[p], p);
			// make 0 ,1 and 2 invalid and add associated triangles to f_T
			set[p + 2] = 0;

		} else {

			if (set[p + 1] <= 6) {

				check = 0;
				tri = set[p + 1];
				v = p + 4;
				flag = 0;
				while (tri != 0) {

					check = 0;
					while (check < c) {
						if (f_t[check] == set[v]) {
							flag = 1;

							//printf("caught %d\n",set[p]);
							break;
						}
						check++;

					}
					if (flag == 1) {
						break;
					}

					v++;
					tri--;
				}

				if (flag == 1) {

					set[p + 2] = 0;
				} else if (flag == 0) {
					tri = set[p + 1];
					v = p + 4;
					while (tri != 0) {

						f_t[c] = set[v];
						tri--;
						v++;
						c++;
					}
					set[p + 2] = 1;
				}

			} else {
				set[p + 2] = 0;
			}

		}

		p = p + 10;

	}

	printf("validation done\n");

	p = 0;
	while (p < j) {

		p = p + 10;

	}

	p = 0;
	int degree5 = 0;
	int degree6 = 0;
	int degree4 = 0;
	int degree3 = 0;
	int degree2 = 0;
	int degree1 = 0;
	int *valid1 = (int *) malloc(270009 * sizeof(int));
	int v1 = 0;
	int check1 = 0;
	while (p < j) {

		int count = 0;
		int flag = 0;
		int degree = set[p + 1];
		v = p + 4;
		if (set[p + 2] == 1) {
			check1++;

			if (degree == 3) {
				degree3++;
			} else if (degree == 2) {
				degree2++;
			} else if (degree == 1) {
				degree1++;
			} else if (degree == 4) {
				degree4++;
			} else if (degree == 5) {
				degree5++;
			} else if (degree == 6) {
				degree6++;
			}

			while (degree > 0) {

				flag = 0;
				count = 0;
				while (count < v1) {
					if (valid1[count] == set[v]) {
						flag = 1;
						break;
					}
					count++;
				}

				if (flag == 0) {
					valid1[v1] = set[v];
					v1++;
				} else if (flag == 1) {

				}

				v++;
				degree--;

			}

		}

		p = p + 10;

	}

	printf("number of vertex selected 1st %d\n", check1);

	printf(" degree with 1 %d\n", degree1);
	printf(" degree with 2 %d\n", degree2);
	printf(" degree with 3 %d\n", degree3);
	printf(" degree with 4 %d\n", degree4);
	printf(" degree with 5 %d\n", degree5);
	printf(" degree with 6 %d\n", degree6);

	p = 0;
	while (p < v1) {
		//printf("caught valid %d\n", valid1[p]);
		p++;
	}
	printf("triangles to be removed are %d\n", p);
	printf("\n");

	int *new_triangles = (int *) calloc(m * 30, sizeof(int));

	temp_tri = triangles;
	k = 0;
	index = 0;
	while (k < m) {
		//printf("at k %d, %d , %d , %d \n", k, *temp_tri, *(temp_tri + 1),*(temp_tri + 2));

		flag = 0;
		p = 0;
		while (p < v1) {
			if (valid1[p] == k) {
				//printf("caught k %d\n", k);
				flag = 1;
				break;
			}
			p++;
		}

		if (flag == 0) {

			new_triangles[new_index] = *temp_tri;
			new_index++;
			new_triangles[new_index] = *(temp_tri + 1);
			new_index++;
			new_triangles[new_index] = *(temp_tri + 2);
			new_index++;
			new_triangles[new_index] = 1;
			new_index++;
			new_triangles[new_index] = k;
			new_index = new_index + 6;
			index++;

		} else if (flag == 1) {

		}

		temp_tri = temp_tri + 3;
		k++;
	}

	int new_formed = index;
	printf("new formed triangles before triangulation %d\n", new_formed);

	/*
	 p = 0;
	 index = 0;
	 while (p < new_index) {
	 printf("at p %d, %d,%d,%d, degree %d,(%d,%d,%d,%d,%d,%d)\n", index, new_triangles[p],
	 new_triangles[p + 1], new_triangles[p + 2], new_triangles[p + 3], new_triangles[p + 4] ,new_triangles[p + 5], new_triangles[p + 6],
	 new_triangles[p + 7],new_triangles[p + 8],new_triangles[p + 9]);
	 p = p + 10;
	 index++;
	 }
	 */

	printf("start triangulation\n");

	int vcount = 0;
	int total_tri5 = 0;
	int total_tri6 = 0;

	re_tri = 0;

	p = 0;
	int *z = (int *) calloc(sizeof(int), 1);
	int *b = (int *) calloc(sizeof(int), 1);
	int *d = (int *) calloc(sizeof(int), 1);
	int *e = (int *) calloc(sizeof(int), 1);
	int *a = (int *) calloc(sizeof(int), 1);
	int *f = (int *) calloc(sizeof(int), 1);
	int degree_valid = 0;
	temp_tri = triangles;

	point = points;
	int num_of_prev_tri = 0;
	int num = 0;
	while (p < j) {
		int *vertex = (int *) malloc(18 * sizeof(int));
		int *previous_tri = (int *) calloc(sizeof(int), 6);
		int t = 0;
		num_of_prev_tri = set[p + 1];
		if (set[p + 2] == 1 && set[p + 1] == 3) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 3];

				vcount++;
				vertex[vcount] = temp_tri[(t * 3) + 1];

				vcount++;
				vertex[vcount] = temp_tri[(t * 3) + 2];

				vcount++;
				degree_valid--;
				v++;
			}

			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			//printf("find_a is %d, ", *a);

			b = find_B(vcount, b, a, vertex, set[p], points);
			//printf("b is %d, ", *b);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			//printf("z is %d, ", *z);

			new_triangles = triangle3(points, a, b, z, new_triangles,
					num_of_prev_tri, previous_tri);

			//printf("end of triagnle 3\n");

		} else if (set[p + 2] == 1 && set[p + 1] == 4) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;
				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 3];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 1];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 2];
				vcount++;

				degree_valid--;
				v++;
			}

			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			//printf("find_a is %d, ", *a);

			b = find_B(vcount, b, a, vertex, set[p], points);
			//printf("b is %d, ", *b);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			//printf("z is %d, ", *z);

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			//printf("d is %d, ", *d);

			new_triangles = triangle4(points, a, b, z, d, new_triangles,
					num_of_prev_tri, previous_tri);
			//printf("end of triagnle 4\n");

		} else if (set[p + 2] == 1 && set[p + 1] == 5) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 3];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 1];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 2];
				vcount++;

				degree_valid--;
				v++;
			}

			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			//printf("find_a is %d, ", *a);

			b = find_B(vcount, b, a, vertex, set[p], points);
			//printf("b is %d, ", *b);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			//printf("z is %d, ", *z);

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			//printf("d is %d, ", *d);

			e = find_vertex(vcount, e, d, z, vertex, set[p], points);
			//printf("e is %d", *e);

			new_triangles = triangle5(points, a, b, z, d, e, new_triangles,
					num_of_prev_tri, previous_tri);

			total_tri5++;

			//printf("end of triagnle 5\n");

		} else if (set[p + 2] == 1 && set[p + 1] == 6) {

			//printf("point selected %d, degree is %d\n", set[p], set[p + 1]);
			vcount = 0;
			degree_valid = set[p + 1];
			v = p + 4;
			num = 0;
			while (degree_valid != 0) {
				t = set[v];
				previous_tri[num] = set[v];
				num++;

				/*
				 printf("%d( %d(%d,%d),%d(%d,%d),%d(%d,%d) )\n", set[v],
				 temp_tri[t * 3], point[(temp_tri[t * 3]) * 2],
				 point[((temp_tri[t * 3]) * 2) + 1],
				 temp_tri[(t * 3) + 1],
				 point[(temp_tri[(t * 3) + 1]) * 2],
				 point[((temp_tri[(t * 3) + 1]) * 2) + 1],
				 temp_tri[(t * 3) + 2],
				 point[(temp_tri[(t * 3) + 2]) * 2],
				 point[((temp_tri[(t * 3) + 2]) * 2) + 1]);
				 */

				vertex[vcount] = temp_tri[t * 3];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 1];
				vcount++;

				vertex[vcount] = temp_tri[(t * 3) + 2];
				vcount++;

				degree_valid--;
				v++;
			}

			// vertex a
			a = find_A(vcount, a, vertex, set[p], points);
			//printf("find_a is %d, ", *a);

			b = find_B(vcount, b, a, vertex, set[p], points);
			//printf("b is %d, ", *b);

			z = find_vertex(vcount, z, b, a, vertex, set[p], points);
			//printf("z is %d, ", *z);

			d = find_vertex(vcount, d, z, b, vertex, set[p], points);
			//printf("d is %d, ", *d);

			e = find_vertex(vcount, e, d, z, vertex, set[p], points);
			//printf("e is %d", *e);

			f = find_vertex(vcount, f, e, d, vertex, set[p], points);
			//printf("f is %d", *f);

			new_triangles = triangle6(points, a, b, z, d, e, f, new_triangles,
					num_of_prev_tri, previous_tri);

			total_tri6++;
			//printf("end of triagnle 6\n");

		}

		p = p + 10;

	}

	printf("re_tri , number tri retriagulated %d\n", re_tri);

	printf("new index is %d\n", new_index);

	p = 0;
	index = 0;
	while (p < new_index) {
		/*
		 printf("at p %d, %d,%d,%d, degree %d,(%d,%d,%d,%d,%d,%d)\n", index, new_triangles[p],
		 new_triangles[p + 1], new_triangles[p + 2], new_triangles[p + 3], new_triangles[p + 4] ,new_triangles[p + 5], new_triangles[p + 6],
		 new_triangles[p + 7],new_triangles[p + 8],new_triangles[p + 9]);
		 */
		p = p + 10;
		index++;
	}

	int num_of_points = index;

	new_formed = num_of_points - new_formed;

	printf("triangles formed after re trianulation %d\n", new_formed);
	printf("total number of triangles %d\n", num_of_points);

	tri_start[ts] = 0;
	ts++;
	tri_start[ts] = num_of_points;
	ts++;

	new_triangles = Retriangulation(num_of_points, new_triangles, n,
			tri_start[0], tri_start[1], points);

	return new_triangles;

}

ploc_t *create_ploc(int *point, int *triangles, int n, int m) {

	ploc_t *result;
	result = (ploc_t*) malloc(sizeof(ploc_t));

	int *vertex_degree;
	vertex_degree = find_degree(point, triangles, m, n);

	return result;
}

int query_ploc(ploc_t *pl, int x, int y) {

	return 1;
}

int main() {

	clock_t t;
	t = clock();

	int points[90003][2];
	int triangles[180002][3];
	int i, j, k;
	k = 0;
	for (i = 0; i < 300; i++) {
		for (j = 0; j < 300; j++) {
			points[k][0] = 15 * i;
			points[k][1] = 15 * j;
			k += 1;
		}
	}
	printf("first point in main %d\n", points[1][0]);
	points[k][0] = -4500;
	points[k++][1] = -15;
	points[k][0] = 9000;
	points[k++][1] = -15;
	points[k][0] = 2250;
	points[k++][1] = 9000;
	printf("Prepared %d points\n", k);
	k = 0;
	triangles[k][0] = 90000;
	triangles[k][1] = 90001;
	triangles[k++][2] = 90002;
	for (i = 0; i < 299; i++) {
		triangles[k][0] = i;
		triangles[k][1] = i + 1;
		triangles[k++][2] = 90000;
	}
	triangles[k][0] = 299;
	triangles[k][1] = 90000;
	triangles[k++][2] = 90002;
	for (i = 0; i < 299; i++) {
		triangles[k][0] = 299 + 300 * i;
		triangles[k][1] = 299 + 300 * (i + 1);
		triangles[k++][2] = 90002;
	}
	triangles[k][0] = 90002;
	triangles[k][1] = 89999;
	triangles[k++][2] = 90001;
	for (i = 0; i < 299; i++) {
		triangles[k][0] = 299 * 300 + i;
		triangles[k][1] = 299 * 300 + i + 1;
		triangles[k++][2] = 90001;
	}
	triangles[k][0] = 90000;
	triangles[k][1] = 89700;
	triangles[k++][2] = 90001;
	for (i = 0; i < 299; i++) {
		triangles[k][0] = 300 * i;
		triangles[k][1] = 300 * (i + 1);
		triangles[k++][2] = 90000;
	}
	for (i = 0; i < 299; i++) {
		for (j = 0; j < 299; j++) {
			triangles[k][0] = 300 * i + j;
			triangles[k][1] = 300 * (i + 1) + j;
			triangles[k++][2] = 300 * i + j + 1;
			triangles[k][0] = 300 * (i + 1) + j + 1;
			triangles[k][1] = 300 * (i + 1) + j;
			triangles[k++][2] = 300 * i + j + 1;
		}
	}
	printf("Prepared %d triangles\n", k);
	{
		ploc_t *pl;
		pl = create_ploc(points, triangles, 90003, 180002);
		for (i = 0; i < 10000; i++) {
			int a, b, c, x, y, t;
			j = (rand() % 180001) + 1;
			a = triangles[j][0];
			b = triangles[j][1];
			c = triangles[j][2];
			x = (points[a][0] + points[b][0] + points[c][0]) / 3;
			y = (points[a][1] + points[b][1] + points[c][1]) / 3;
			t = query_ploc(pl, x, y);
			if (t != j) {
				printf("Error on triangle %d, misidentified as triangle %d\n",
						j, t);
				printf(
						"Point (%d,%d) should be in triangle (%d,%d), (%d,%d), (%d,%d)\n",
						x, y, points[a][0], points[a][1], points[b][0],
						points[b][1], points[c][0], points[c][1]);
				printf(
						"Instead claimed in triangle (%d,%d), (%d,%d), (%d,%d)\n",
						points[triangles[t][0]][0], points[triangles[t][0]][1],
						points[triangles[t][1]][0], points[triangles[t][1]][1],
						points[triangles[t][2]][0], points[triangles[t][2]][1]);
				t = clock() - t;
				double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds

				printf("took %f seconds to execute \n", time_taken);
				printf("END\n");
				exit(0);
			}
		}
	}
	printf("Passed test\n");

}
