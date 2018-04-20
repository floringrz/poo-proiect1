//
//  main.cpp
//  poo proiect final
//
//  Created by Garzon Najar Percy Florin on 4/19/18.
//  Copyright © 2018 Garzon Najar Percy Florin. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

class graf{
    
public:
    
    class nod{
    public: int valoare;
        int grad;
        int v[100];// vectorul de adiacenta
        
        
    }n[100];
    int nrnoduri, drum[100][100],ma[100][100],viz[100];
    queue<int> coada;
    graf();
    graf(const graf &g);
   // ~graf();
    void matrice(const graf&g);
    void set_viz(int);
    void conex(const graf&g);
    void ajutor(int);
    void drumuri(const graf&g);
    void dfs_auxiliar(int);     //funtie ajutatoare (pentru void dfs(int) )
    void dfs(int); //parcurgerea grafului in adancime
    void componente_conexe(const graf &g);
   void bfs(int, int,const graf &g);
    void BFS(int x);
    friend graf  operator+( const graf &c,const graf &q);
    void operator=(const graf&g);
    
    friend istream & operator>>(istream&in, graf &g);
    friend ostream &operator<<(ostream&out,graf &c);
    
    friend bool operator ==(const graf &c, const graf&q);
    friend bool operator !=(const graf&c,const graf &q);
    
    friend bool operator<(const graf &c, const graf &q);
    friend bool operator>(const graf &c, const graf &q);
   
    
};
graf::graf()
{
    nrnoduri=0;
    
}

istream &operator>>(istream&in, graf &g)
{cout<<"Cate noduri vreti sa aiba graful?"<<endl;
    
    in>>g.nrnoduri;
    int i,x,j, nr;
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=g.nrnoduri;j++)
        g.ma[i][j]=0;
        }
    for(i=1;i<=g.nrnoduri;i++)
    {
        int Grad=0;
        g.n[i].valoare=i;
        cout<<"cate noduri sunt adiacente cu nodul "<<i<<"?";
        cout<<endl;
        in>>nr;
        if(nr)
        cout<<"dati in ordine crescatoare nodurile care sunt adiacente cu nodul "<<i;
        cout<<endl;
        for(j=1;j<=nr;j++)
        {Grad=Grad+1;
            in>>x;
            g.n[i].v[Grad]=x;
            g.n[i].grad= Grad;
            g.ma[i][x]=1;
            g.ma[x][i]=1;
        }
    
        
        
    }
    return in;
}
ostream&operator <<(ostream&out,  graf &g){
    int i,j;
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=g.n[i].grad;j++)
    {if(g.n[i].v[j]>g.n[i].valoare)
        cout<<g.n[i].valoare<<" "<<g.n[i].v[j]<<endl;
        
    }
        
    }
    return out;
}


bool operator==(const graf&c,const graf &q){
    int i,j,verifica=1;
    if(c.nrnoduri!=q.nrnoduri)
        verifica=0;
    
    for(i=1;i<=c.nrnoduri;i++)
    {if(c.n[i].grad!=q.n[i].grad)
        verifica=0;}
    
    for(i=1;i<=c.nrnoduri;i++)
    {for(j=1;j<=c.n[i].grad;j++)
        if(c.n[i].v[j]!=q.n[i].v[j])
            verifica=0;}
    
    if(verifica==1)
        return 1;
    else return 0;}
bool operator!=(const graf&c,const graf &q){
    return!(c==q);
}
bool operator<(const graf &c, const graf &q){
    if(c.nrnoduri<q.nrnoduri)
        return 1;
    else return 0;
}
bool operator>(const graf&c,const graf &q )
{if(c.nrnoduri<q.nrnoduri)
    return 0;
else return 1;
    
}
graf::graf(const graf &g){
    int i,j;
    nrnoduri=g.nrnoduri;
    for(i=1;i<=g.nrnoduri;i++)
    {viz[i]=g.viz[i];
        n[i].grad=g.n[i].grad;
        n[i].valoare=g.n[i].valoare;}
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=nrnoduri;j++)
        ma[i][j]=g.ma[i][j];
        
        n[i].v[j]=g.n[i].v[j];
    }
    
}
void  graf::operator=(const graf &g){
    int i,j;
    nrnoduri=g.nrnoduri;
    for(i=1;i<=g.nrnoduri;i++)
    {viz[i]=g.viz[i];
        n[i].grad=g.n[i].grad;
        n[i].valoare=g.n[i].valoare;}
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=nrnoduri;j++)
        ma[i][j]=g.ma[i][j];
        
        n[i].v[j]=g.n[i].v[j];
        
    }
}
graf operator+( const  graf &c,const graf &g){
    int i,j;
  class  graf nou;
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=g.nrnoduri;j++)
    {if(c.ma[i][j]!=0|| g.ma[i][j]!=0)
        { nou.ma[i][j]=1;
        nou.n[i].valoare=i;
            nou.n[i].v[j]=j;
            nou.n[i].grad++;
        }
      
    }}
   
    return nou;
}
void graf::ajutor(int nod)
{    viz[nod]=1;
    for(int k=1;k<=nrnoduri;k++)
        if(ma[nod][k]==1&&viz[k]==0)
            ajutor(k);
}
void graf::set_viz(int nr)
{
    int i;
    for(i=1;i<=nrnoduri;i++)
        viz[i]=nr;
}
 void graf::matrice(const graf &g){
     
     int i,j;
     cout<<"Matricea de adiacenta:"<<endl;
     for(i=1;i<=g.nrnoduri;i++)
     {for(j=1;j<=g.nrnoduri;j++)
         cout<<g.ma[i][j]<<" ";
         cout<<endl;
         }
     
 }
void graf::drumuri(const graf&g){
    int nod,i,j;
    for(nod=1;nod<=g.nrnoduri;nod++)
    {for(j=1;j<=g.nrnoduri;j++)
        viz[j]=0;
        ajutor(nod);
        viz[nod]=0;
        for(j=1;j<=g.nrnoduri;j++)
            drum[nod][j]=viz[j];
    }
    cout<<endl<<"matricea drumurilor "<<endl;
    for(i=1;i<=g.nrnoduri;i++)
    {for(j=1;j<=g.nrnoduri;j++)
    cout<<drum[i][j]<<" ";
        cout<<endl;}
}
void graf::conex(const graf &g)
{
    int i,  c[50], p=1, u=1, x=1;
    this->set_viz(0);
    c[1]=x;
    viz[x]=1;
    while(p<=u)
    {
        x=c[p++];
        for(i=1;i<=g.nrnoduri;i++)
            if(g.ma[x][i]==1&&viz[i]==0)
            {
                c[++u]=i;
                viz[i]=1;
            }
    }
    if(u==g.nrnoduri)
        cout<<"Graful este conex";
    else
        cout<< "Graful nu este conex";
}
            void graf::bfs(int x, int k, const graf&g)
    {
        int i,  p=1, u=1, c[50];
        this->set_viz(0);
        c[1]=x;
        viz[x]=k;
        while(p<=u)
        {
            x=c[p++];
            for(i=1;i<=g.nrnoduri;i++)
                if(g.ma[x][i]==1&&viz[i]==0)
                {
                    c[++u]=i;
                    viz[i]=k;
                }
        }
    }
void graf::componente_conexe(const graf &g)
{
    int k, i, j;
    k=0;
    this->set_viz(0);
    for(i=1;i<=g.nrnoduri;i++)
        if(g.viz[i]==0)
        {
            k++;
            this->bfs(i,k,g);
        }
    if(k==1)
    {
        cout<<'\n'<<"      O singura componenta conexa: ";
        for(i=1;i<=g.nrnoduri;i++)
            cout<<i<<" ";
    }
    else
    {
        cout<<"\n      "<<k<<" componente conexe.\n";
        for(i=1;i<=k;i++)
        {
            cout<<"   Componenta "<<i<<": ";
            for(j=1;j<=g.nrnoduri;j++)
                if(g.viz[j]==i)
                    cout<<j<<" ";
            cout<<'\n';
        }
    }
}
void graf::dfs_auxiliar(int x)
{
    int j;
    cout<<x<<" ";
    viz[x]=1;
    for(j=1;j<=nrnoduri;j++)
        if(ma[x][j]==1&&viz[j]==0)
            this->dfs_auxiliar(j);
}
void graf::dfs(int x)
{
    
    this->set_viz(0);
    this->dfs_auxiliar(x);
}

void graf:: BFS(int x){
    int i;
    this->set_viz(0);
    coada.push(x);
    
    viz[x]=1;
    while(coada.empty()!=1)
    {for(i=1;i<=nrnoduri;i++)
    {if(viz[i]==0 && ma[coada.front()][i]==1)
    {coada.push(i);
        viz[i]=1;
        
    }
        
    
    }
        cout<<coada.front()<<" ";
        coada.pop();
    }}
int main()
{cout<<"Proiect Programare Orientata pe Obiecte-- Grafuri neorientate"<<endl<<endl;
    cout<<"Meniu:"<<endl;
    int ok=0,v;
    class graf g;
    class graf f;
    class graf nou;
    while(ok==0){
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"1.Cititi primul graf."<<endl;
        cout<<"2.Cititi al doilea graf."<<endl;
        cout<<"3. Parcurgerea in latime pentru primul graf."<<endl;
        cout<<"4.Parcurgerea in latime pentru al doilea graf."<<endl;
        cout<<"5.Parcurgerea in adancime pentru primul graf."<<endl;
        cout<<"6.Parcurgerea in adancime pentru al doilea graf."<<endl;
        cout<<"7.Aflarea componentelor conexe pentru primul graf."<<endl;
        cout<<"8.Aflarea componentelor conexe pentru al doilea gra.f"<<endl;
        cout<<"9.Este primul graf conex?"<<endl;
        cout<<"10.Este al doilea graf conex?"<<endl;
        cout<<"11.Afisarea primului graf ca lista de muchii."<<endl;
        cout<<"12.Afisarea celui de al doilea graf ca lista de muchii."<<endl;
        cout<<"13.Afisarea matricii de adiacenta si de drumuri pentru primul graf."<<endl;
        cout<<"14.Afisarea matricii de adiacenta si de drumuri pentru al doilea graf."<<endl;
        cout<<"15.Adunarea a doua grafuri."<<endl;
        cout<<"16. Inchidere program."
        <<endl;
        cout<<"------------------------------------------------------------"<<endl;
        cout<<"Selectati o instructiune: ";
        cin>>v;
        cout<<endl;
        switch (v)
        {
            case 1:
            {cout<<endl;
                cin>>g;
                cout<<endl;
                break;
        }
            case 2:{
                cout<<endl;
                cin>>f;
                cout<<endl;
                break;
            }
            case 3:{
                int x;
                cout<<endl;
                cout<<"Spuneti de unde sa se inceapa parcurgerea: ";
                cin>>x;
                g.BFS(x);
                cout<<endl;
                break;
                
            }
            case 4:{
                int x;
                cout<<endl;
                cout<<"Spuneti de unde sa se inceapa parcurgerea: ";
                cin>>x;
                f.BFS(x);
                cout<<endl;
                break;
                
            }
            case 5:{
                int x;
                cout<<endl;
                cout<<"Spuneti de unde sa se inceapa parcurgerea: ";
                cin>>x;
                g.dfs(x);
                cout<<endl;
                break;
                
            }
            case 6:{
                int x;
                cout<<endl;
                cout<<"Spuneti de unde sa se inceapa parcurgerea: ";
                cin>>x;
                f.dfs(x);
                cout<<endl;
                break;
                
            }
            case 7:{
                
                cout<<endl;
              
                g.componente_conexe(g);
                cout<<endl;
                break;
                
            }
            case 8:{
                
                cout<<endl;
                
                f.componente_conexe(f);
                cout<<endl;
                break;
                
            }
            case 9:{
               
                
                g.conex(g);
                cout<<endl;
                break;
                
            }
        
            case 10:{
                
                
                f.conex(f);
                cout<<endl;
                break;
                
            }
            case 11:{
                
                
                cout<<g;
                cout<<endl;
                break;
                
            }
            case 12:{
                cout<<endl;
                cout<<f;
                cout<<endl;
              
                break;
                
            }
            case 13:{
                
                
                g.matrice(g);
                g.drumuri(g);
                cout<<endl;
                
                break;
                
            }
            case 14:{
                
                
                f.matrice(f);
                f.drumuri(f);
                cout<<endl;
                
                break;
                
            }
            case 15:{
                cin>>f;
                cin>>g;
                cout<<endl;
                nou=f+g;
                cout<<nou;
                cout<<endl;
                break;
            }
            case 16:{
                ok=1;
                break;
            }
        }
        
    }

}
