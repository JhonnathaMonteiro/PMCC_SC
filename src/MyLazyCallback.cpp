#include "my_lazy_callback.h"
#include "min_cut.h"
#include "data_reader.h"

//construtor da classe
MyLazyCallback::MyLazyCallback(IloEnv env, const IloBoolVarArray &ref_l, DataReader<double> &data) : IloCplex::LazyConstraintCallbackI(env), d(data)
{
    vars_l = ref_l;
}

//metodo que retorna copia do callback. (Exigencia do CPlex)
IloCplex::CallbackI *MyLazyCallback::duplicateCallback() const
{
    return new (getEnv()) MyLazyCallback(getEnv(), vars_l, d);
}

void MyLazyCallback::main()
{

    //-----------Teste para instancia instancia_teste_mini ---------------
    // vou considerar: 0,...,24 as cores
    // valores da diagonal principal = -1
    // e 25 ( = d.L) ausencia de cor (vertice nao conectado)
    // instancia_teste_mini:
    //
    //  -1  5  0  0 25  4
    //   5 -1 16  4  3 25
    //   0 16 -1  1  1 16
    //   0  4  1 -1 20  2
    //  25  3  1 20 -1  0
    //   4 25 16  2  0 -1

    //--------------------------------------------------------------------
    IloEnv env = getEnv();

    //faz a leitura dos valores das variaveis
    IloNumArray values_l(getEnv(), vars_l.getSize());
    getValues(values_l, vars_l); // <-- Vetor solucao do cplex

    //criando matriz para o problema do fluxo maximo
    int label_index;

    //iterando pela matriz triangular superior
    int dim = d.getV();
    std::vector<std::vector<double>> G = d.getG();
    for (int row = 0; row < dim - 1; ++row)
    {
        for (int col = row + 1; col < dim; ++col)
        {
            label_index = G[row][col];

            // COM INVERSAO DOS VALORES DA MATRIZ ----------------------------------------------------------
            // G[row][col] = 1 - values_l[label_index]; // <-- Assim n funciona (inversao dos valores)

            // SEM INVERSAO DOS VALORES DA MATRIZ ----------------------------------------------------------
            G[row][col] = values_l[label_index]; // <-- Assim funciona (sem inversao dos valores)
            G[col][row] = G[row][col];
        }
    }

    printf("=============================\n");
    for (size_t i = 0; i < d.getL(); i++)
    {
        printf("%d\n", d.getL());
    }
    printf("=============================\n");
    // for (size_t i = 0; i < d.getL(); i++)
    // {
    //     printf(" %.2lf\n", values_l[i]);
    // }

    // Min-cut
    int a = 2;
    Cut min_cut = minCut(G, a, dim);
    std::set<int> colors = min_cut.getColors();
    printf("%d\n", min_cut.getCost());

    // Criando a restricao do corte
    double colors_sum = 0;
    IloExpr rExpr(env);
    for (auto &color : colors)
    {
        rExpr += vars_l[color];
        colors_sum += values_l[color];
    }

    // Verificar se deve adicionar o corte
    if (colors_sum < 1)
    {
        // Adicao da restricao do corte
        add(rExpr >= 1);
    }
    rExpr.end();
}
