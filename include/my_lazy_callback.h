#ifndef MY_LAZY_CALLBACK_H
#define MY_LAZY_CALLBACK_H

#include <ilcplex/ilocplex.h>

#include "data_reader.h"

class MyLazyCallback : public IloCplex::LazyConstraintCallbackI
{

public:
    //construtor
    // MyLazyCallback(IloEnv env, const IloBoolVarArray &ref_l, Data &d);
    MyLazyCallback(IloEnv env, IloBoolVarArray const &ref_l, DataReader<double> &data);

    //metodo que retorna copia do callback. (Exigencia do CPlex)
    IloCplex::CallbackI *duplicateCallback() const;

    //metodo executado pelo Callback do Cplex (Exigencia do CPlex)
    void main();

private:
    //guarda os valores das variaveis
    IloBoolVarArray vars_l;

    //dados
    DataReader<double> &d;
};

#endif
