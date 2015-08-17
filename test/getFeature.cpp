#include "head.h"

#define trainData "train.txt"
#define testData "predict.txt"

#define inputData trainData
#define BUF_SIZE 100000

#include "text.h"
#include "Blog.h"
#define N 50000

char buf[BUF_SIZE];

vector<Blog> userBlog[N+10];
Blog statics[N+10];

vector<Blog> train;
vector<Blog> test;

map<string, int> stringToId;
vector<string> keyWords;
set<int> unHotUser;
int idx = 0;

void outputUserInfo(){
	string fUserName = "user.out";
	FILE *fUser = fopen(fUserName.c_str(), "w");
	if (fUser==NULL){
		fprintf(stderr, "open file<%s> failed\n", fUserName.c_str());
		return;
	}

	fprintf(fUser, "cnt,forward,comment,like\n");
	repf(i, 1, idx){
		int cnt = sz(userBlog[i]);
		fprintf(fUser, "%d,%.8f,%.8lf,%.8lf\n",
				cnt,
				statics[i].forward*.1/cnt,
				statics[i].comment*1./cnt,
				statics[i].like*1./cnt
			   );
	}
}

void readTest(){
	FILE *foutput = fopen("test.out", "w");
	if (foutput==NULL){
		fprintf(stderr, "oepn file<%s> failed\n", "test.out");
		return;
	}

	fprintf(foutput, "cnt,uid,userForward,userComment,userLike,text,http,face,forward,comment,like,userId,blogId,date");

	/*
	rep(i, sz(keyWords)) 
		fprintf(foutput, ",word%d", i);
	*/

	fprintf(foutput, "\n");


	rep(i, sz(test)){
		Blog &blog = test[i];
		int idx = stringToId[blog.userId];

		int cnt = sz(userBlog[idx]);
		Blog &stat = statics[idx];
		fprintf(foutput, "%d,%d,%.8lf,%.8lf,%.8lf,%d,%d,%d,%d,%d,%d,%s,%s,%s",
				cnt,
				idx,
				stat.forward*1./cnt,
				stat.comment*1./cnt,
				stat.like*1./cnt,
				blog.text.len,
				blog.text.http,
				blog.text.face,
				blog.forward,
				blog.comment,
				blog.like,
				blog.userId.c_str(),
				blog.blogId.c_str(),
				blog.date.c_str()
				);

		/*
		rep(j, sz(keyWords)){
			fprintf(foutput, ",%d", blog.text.getCnt(keyWords[j]));
		}
		*/
		fprintf(foutput, "\n");

	}

	fclose(foutput);
}


void readTrain(){
	string fTextName = "chinese.out";
	FILE *fText = fopen(fTextName.c_str(), "w");
	if (fText == NULL){
		fprintf(stderr, "open file<%s> failed\n", fTextName.c_str());
		return;
	}

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
		if (rand()%100<=80)
			train.push_back(blog);
		else
			test.push_back(blog);
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
		fprintf(fText, "%s", blog.text.s.c_str());
	}

	// get statics for each users

	repf(i, 1, idx){
		rep(j, sz(userBlog[i]))
			statics[i] = statics[i] + userBlog[i][j];
		if (statics[i].forward+statics[i].comment+statics[i].like==0)
			unHotUser.insert(i);
	}


	//put test data into userBlog

	rep(i, sz(test)){
		Blog &blog = test[i];
		int userIdx = stringToId[blog.userId];
		if (userIdx == 0){
			userIdx = ++idx;
			stringToId[blog.userId] = userIdx;
		}
		userBlog[userIdx].push_back(blog);
		fprintf(fText, "%s", blog.text.s.c_str());
	}

	// output features of each train data


	fprintf(foutput, "cnt,uid,userForward,userComment,userLike,forward,comment,like,text,http,face");
	fprintf(foutput, "\n");

	rep(i, sz(train)){
		Blog &blog = train[i];
		int userIdx = stringToId[blog.userId];

		if (unHotUser.find(userIdx) != unHotUser.end())
			continue;

		Blog &stat = statics[userIdx];
		int cnt = userBlog[userIdx].size();

		fprintf(foutput, "%d,%d,%.8lf,%.8lf,%.8lf,%d,%d,%d,%d,%d,%d", 
				cnt,
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
		fprintf(foutput, "\n");
	}
	fclose(foutput);

}

void readKeyWord(){
	string fileName = "KeyWords/keyWord.out";
	FILE *file = fopen(fileName.c_str(), "r");

	char tmp[100];

	while (fgets(buf, BUF_SIZE, file)){
		sscanf(buf, "%s", tmp);
		keyWords.push_back(tmp);
	}
}

int main(){
	srand(time(NULL));
	readKeyWord();
	readTrain();	
	readTest();
//	outputUserInfo();
	return 0;
}

