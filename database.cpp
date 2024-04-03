#include "database.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include <vector>




Entry *create(Type type, std::string key, void *value){
   
    
    
    Entry* newEntry = new Entry;
    newEntry->type = type;
    newEntry->key = key;
    if (type == INT) {
        newEntry->value = new int(*(static_cast<int*>(value)));
    } else if (type == DOUBLE) {
        newEntry->value = new double(*(static_cast<double*>(value)));
    } else if (type == STRING) {
        newEntry->value = new std::string(*(static_cast<std::string*>(value)));
    } else {
        newEntry->value = value;
    }

    return newEntry;

};

void print(Array* array){//for
    int size =array->size;
    if(array->type==ARRAY){ //배열포함
        for (int k = 0; k < size; k++){
            std::cout << "[";
            Array* nestedArray = static_cast<Array*>(array->items);
            Array* nestedArr = &nestedArray[k];
            
            
            
            

            
            print(nestedArr);
            std::cout << "]";
            if (k!=size-1)
            {
                std::cout <<", ";
            }
            
           
            
            
           
    }
    
    
    
    }else //배열 미포함
    {
        if (array->type == STRING) {
            
            
            
            std::string* str = static_cast<std::string*>(array->items);
            
            for (int i = 0; i < size; i++)
            {
                std::cout << "\"";
                std::cout << str[i];
                std::cout << "\"";
                if (i!=size-1)
                {
                std::cout <<", ";
                }
                
            }
            
            

            

            
        } else if (array->type == INT) {
            
            int* intt = static_cast<int*>(array->items);
            
            for (int i = 0; i < size; i++)
            {
                
                std::cout << intt[i];
                if (i!=size-1)
                {
                std::cout <<", ";
                }
            }
            
            
        } else if (array->type == DOUBLE) {
            
            double* dou = static_cast<double*>(array->items);
            
            for (int i = 0; i < size; i++)
            {
                
                std::cout << dou[i];
                if (i!=size-1)
                {
                std::cout <<", ";
                }
            }
            
        }
    
    
    }
    
    
    
    
}
void list(Database database){
    for (int i = 0; i < database.size; i++)
    {
        std::cout << database.entries[i].key << ": ";
        if (database.entries[i].type == STRING) {
            std::cout << "\"" << *(static_cast<std::string*>(database.entries[i].value)) << "\"";
        } else if (database.entries[i].type == INT) {
            std::cout << *(static_cast<int*>(database.entries[i].value));
        } else if (database.entries[i].type == DOUBLE) {
            std::cout << *(static_cast<double*>(database.entries[i].value));
        } else if(database.entries[i].type == ARRAY){
            
            std::cout << "[";
            print(static_cast<Array*>(database.entries[i].value));
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

void init(Database &database){
    database.capacity=10;
    database.entries = new Entry[database.capacity];
    database.size=0;
};
void addData(Database &database, Entry *entry){
    if (database.size>=database.capacity)
    {
       Entry* temp = new Entry[database.capacity*2];
       for (int i = 0; i < database.size; i++)
       {
        temp[i]=database.entries[i];
       }
       delete database.entries;
       database.entries=temp;
       database.capacity *=2;

    }
    database.entries[database.size++] = *entry;
    
    
}
Entry* get(Database &database,std::string &key){
    for (int i = 0; i < database.size; i++)
    {
       if (database.entries[i].key==key)
       {
        return &database.entries[i];
       }
       
    }
    return nullptr;
}
void del(Database &database,std::string &key){
    for (int i = 0; i < database.size; ++i) {
        if (database.entries[i].key == key) {
            
            for (int j = i; j < database.size - 1; j++) {
                database.entries[j] = database.entries[j + 1];
            }
            database.size--;
            return; 
        }
    }
}
void destroy(Database &database){
    delete[] database.entries;
    database.capacity=0;
    database.size=0;
}

void arrayAdd(Array* arr){
    //재귀함수로 nestedarray 구현
    int size= arr->size;
    

    for (int i = 0; i < size; i++)
    {
        std::cout << "item[" << i <<"]: type (int, double, string, array): ";
        std::string s;
        std::cin >> s;
        if (s=="array")
        {
            int nested;
            std::cout << "size: ";
            std::cin >> nested;
            Array *a=new Array[nested];
            a->size=nested;
            a->type=ARRAY;
            arrayAdd(a);
            arr->items=a;

        }else if (s=="int")
        {

            int ss;
            
            
            std::cout << "size: ";
            std::cin >> ss;
            Array *a=new Array[ss];
            a->size=ss;
            a->type=INT;
            int *a1=new int[ss];
            for (int j = 0; j < ss; j++)
            {
                std::cout << "item [" << j << "]: ";
                std::cin >> a1[j];
            }
            a->items=a1;
            Array* ary = static_cast<Array*>(arr->items);
            ary[i]=*a;
            
            
        }else if (s=="double")
        {
            int ss;
            
            
            std::cout << "size: ";
            std::cin >> ss;
            Array *ad=new Array[ss];
            ad->size=ss;
            ad->type=DOUBLE;
            double *a3=new double[ss];
            for (int j = 0; j < ss; j++)
            {
                std::cout << "item [" << j << "]: ";
                std::cin >> a3[j];
            }
            ad->items=a3;
            Array* ary = static_cast<Array*>(arr->items);
            ary[i]=*ad;
            
        }else if (s=="string")
        {
            int ss;
            
            
            std::cout << "size: ";
            std::cin >> ss;
            Array *as=new Array[ss];
            as->size=ss;
            as->type=STRING;
            std::string *a2=new std::string[ss];
            for (int j = 0; j < ss; j++)
            {
                std::cout << "item [" << j << "]: ";
                std::cin >> a2[j];
            }
            as->items=a2;
            Array* ary = static_cast<Array*>(arr->items);
            ary[i]=*as;
            
            
        }
        
        
        
    }
    
    


}

int main(){
    Database* database = new Database;
    init(*database);
    bool run = true;
    while (run){
        
        std::string input;
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> input;
        if (input =="list")
        {
            list(*database);
        }else if (input =="add")
        {

            Entry *entry = new Entry;
            std::string key;
            std::string type1;
            
            
            std::cout << "key: " ;
            std::cin >> key;
            del(*database,key);
            std::cout << "type (int, double, string, array): ";
            std::cin >> type1;
            if (type1=="int")
            {
                std::cout << "value: ";
                std::string inputvalue;
                std::cin >> inputvalue;
                int value = std::stoi(inputvalue);
                entry=create(INT,key,&value);
                addData(*database,entry); 
            }else if (type1=="double")
            {
                std::cout << "value: ";
                std::string inputvalue;
                std::cin >> inputvalue;
                double value = std::stod(inputvalue);
                entry=create(DOUBLE,key,&value);
                addData(*database,entry); 
            }else if (type1=="string")
            {
                
                std::cout << "value: ";
                std::string inputvalue;
                std::cin.ignore();
                std::getline(std::cin, inputvalue);
                
                entry=create(STRING,key,&inputvalue);
                addData(*database,entry); 
            }else if(type1=="array"){
                std::string s;
                std::cout << "value: type(int, double, string, array): ";
                
                std::cin >>s;
                int size1;
                std::cout << "size: ";
                std::cin >> size1;
                
                if (s=="int")
                {
                    Array *arr=new Array[size1];
                    arr->size=size1;
                    arr->type=INT;
                    int *a=new int[size1];
                    for (int i = 0; i < size1; i++)
                    {
                        std::cout << "item[" << i << "]: ";
                        
                        std::cin >>a[i];
                    }
                    arr->items=a;
                    Entry *entry=create(ARRAY,key,arr);
                    addData(*database,entry); 

                }else if (s=="double")
                {
                    Array *arr=new Array[size1];
                    arr->size=size1;
                    arr->type=DOUBLE;
                    double *a=new double[size1];
                    for (int i = 0; i < size1; i++)
                    {
                        std::cout << "item[" << i << "]: ";
                        
                        std::cin >>a[i];
                    }
                    arr->items=a;
                    Entry *entry=create(ARRAY,key,arr);
                    addData(*database,entry); 
                }else if (s=="string")
                {
                    Array *arr=new Array[size1];
                    arr->size=size1;
                    arr->type=STRING;
                    std::string *a=new std::string[size1];
                    for (int i = 0; i < size1; i++)
                    {
                        std::cout << "item[" << i << "]: ";
                        
                        std::cin >>a[i];
                    }
                    arr->items=a;
                    Entry *entry=create(ARRAY,key,arr);
                    addData(*database,entry); 
                }else if (s=="array")
                {   

                    Array *arr=new Array[size1];
                    arr->size=size1;
                    arr->type=ARRAY;
                    
                    arrayAdd(arr);
                    Entry *entry=create(ARRAY,key,arr);
                    addData(*database,entry);
                }
                
                
                
                
                        

            }
            
                    
                   
        }else if (input =="get"){
            std::string key;
            std::cout << "key :";
            std::cin >>key;
            Entry *entry =get(*database,key);
            if (entry->type==ARRAY)
            {
                std::cout << entry->key << ": "  ;
                std::cout << "[";
                print(static_cast<Array*>(entry->value));
                std::cout << "]";
            }else{
                std::cout << entry->key << ": "  ;
                
                if (entry->type == STRING) {
                    std::cout << "\"" << *(static_cast<std::string*>(entry->value)) << "\"";
                } else if (entry->type == INT) {
                    std::cout << *(static_cast<int*>(entry->value));
                } else if (entry->type == DOUBLE) {
                    std::cout << *(static_cast<double*>(entry->value));
                }
                



            }
            std::cout << std::endl;
            
        }else if (input =="del")
        {
            std::string key;
            std::cout << "key :";
            std::cin >> key;
            del(*database,key);
        }else if (input =="exit")
        {
            destroy(*database);
            run=false;
        }
            
            
            
            
            
            
            
            
            
            
            
    }
           
            
            
            
            
}
        
        
    
