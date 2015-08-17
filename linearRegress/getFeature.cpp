#define trainData "train.txt"
#define testData "predict.txt"

#define inputData trainData
#define BUF_SIZE 100000

#define N 50000

#include "head.h"
#include "Blog.h"

char buf[BUF_SIZE];

vector<Blog> userBlog[N+10];
vector<Blog> testUserBlog[N+10];

Blog statics[N+10];

vector<Blog> train;
vector<Blog> test;

map<string, int> stringToId;

int idx = 0;

void readTest(){

	
	FILE *foutput = fopen("test.out", "w");
	if (foutput==NULL){
		fprintf(stderr, "oepn file<%s> failed\n", "test.out");
		return;
	}


	fprintf(foutput, "cnt,uid,userForward,userComment,userLike,text,http,face,userId,blogId,date\n");
	rep(i, sz(test)){
		Blog &blog = test[i];
		int idx = stringToId[blog.userId];
		int cnt = sz(userBlog[idx]);
		int cnt2 = sz(testUserBlog[idx]);

		Blog &stat = statics[idx];
		fprintf(foutput, "%d,%d,%.8lf,%.8lf,%.8lf,%d,%d,%d,%s,%s,%s\n",
				cnt+cnt2,
				idx,
				cnt==0?0.:stat.forward*1./cnt,
				cnt==0?0.:stat.comment*1./cnt,
				cnt==0?0.:stat.like*1./cnt,
				blog.text.len,
				blog.text.http,
				blog.text.face,
				blog.userId.c_str(),
				blog.blogId.c_str(),
				blog.date.c_str()
				);
	}

	fclose(foutput);
}


bool outputUserInfo(){
	string fileName = "user.out";
	FILE *fUser = fopen(fileName.c_str(), "w");
	if (fUser == NULL){
		fprintf(stderr, "open file<%s> failed\n", fileName.c_str());
		return false;
	}

	fprintf(fUser, "cnt,forward,comment,like\n");
	repf(i, 1, idx){
		int cnt = sz(userBlog[i]);
		fprintf(fUser, "%d,%.8lf,%.8lf,%.8lf\n", 
				cnt,
				statics[i].forward*1./cnt,
				statics[i].comment*1./cnt,
				statics[i].like*1./cnt
			   );
	}

	return true;
}


void readTrain(){
	FILE *file = fopen(inputData, "r");
	if (file==NULL){
		fprintf(stderr, "open file<%s> failed\n", inputData);
		return;
	}

	string fOutputName = "train.out";
	FILE *foutput = fopen(fOutputName.c_str(), "w");
	if (foutput==NULL){
		fprintf(stderr, "open file<%s> failed\n", fOutputName.c_str());
		return;
	}


	while (fgets(buf, BUF_SIZE, file)){
		Blog blog(buf);
		train.push_back(blog);
	}
	fclose(file);

	rep(i, sz(train)){
		Blog &blog =train[i];
		int userIdx = stringToId[blog.userId];
		if (userIdx == 0){
			userIdx = ++idx;
			stringToId[blog.userId] = userIdx;
		}
		userBlog[userIdx].push_back(blog);
	}

	// get statics for each users

	repf(i, 1, idx){
		rep(j, sz(userBlog[i]))
			statics[i] = statics[i] + userBlog[i][j];
	}

	outputUserInfo();

	// read test data

	FILE *fTest = fopen(testData, "r");
	if (fTest == NULL){
		fprintf(stderr, "open file<%s> failed\n", testData);
		return;
	}


	while (fgets(buf, BUF_SIZE, fTest)){
		Blog blog(buf, true);
		int userIdx = stringToId[blog.userId];
		if (userIdx == 0){
			userIdx = ++idx;
			stringToId[blog.userId] = userIdx;
		}
		testUserBlog[userIdx].push_back(blog);
		test.push_back(blog);
	}

	fclose(fTest);

	// output features of each train data

	fprintf(foutput, "cnt,uid,userForward,userComment,userLike,forward,comment,like,text,http,face\n");
	rep(i, sz(train)){
		Blog &blog = train[i];
		int userIdx = stringToId[blog.userId];
		Blog &stat = statics[userIdx];
		int cnt = userBlog[userIdx].size();
		int cnt2 = testUserBlog[userIdx].size();

		fprintf(foutput, "%d,%d,%.8lf,%.8lf,%.8lf,%d,%d,%d,%d,%d,%d\n", 
				cnt+cnt2,
				userIdx,
				stat.forward*1./cnt,
				stat.comment*1./cnt,
				stat.like*1./cnt,
				blog.forward,
				blog.comment,
				blog.like,
				blog.text.len,
				blog.text.http,
				blog.text.face);
	}
	fclose(foutput);
}

int main(){
	srand(time(NULL));
	readTrain();	
	readTest();
	return 0;
}

