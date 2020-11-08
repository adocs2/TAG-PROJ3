#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

// Faz a ligação do professor com a escola diretamente mantendo a posição de cada habilidade que ele está preenchendo
void assign_Free(Professor *p, Escola *e)
{

    // Se escola tem duas vagas
    if (e->jobs_total == 2)
    {
        // Vincula a escola ao match do professor
        p->match = e;

        // Muda sua disponibilidade para falso pois agora ele está vinculado a uma escola
        p->matched = false;

        // Vicula o professor a escola avaliando cada caso de habilidade. Tentando sempre manter a ordem das preferencias da escola no array de match
        if (p->hab == e->pref[0])
        {
            e->match.insert(e->match.begin(), p);
        }
        else if (e->match.size() > 0)
        {
            if (e->match[0]->hab == e->pref[0])
            {
                e->match.push_back(p);
            }
            else if (e->match[0]->hab == e->pref[1])
            {
                e->match.insert(e->match.begin(), p);
            }
            else
            {
                e->match.push_back(p);
            }
        }
        else
        {
            e->match.push_back(p);
        }
    }
    // Se escola tem uma vagas
    else
    {

        // Vincula a escola ao match do professor
        p->match = e;

        // Muda sua disponibilidade para falso pois agora ele está vinculado a uma escola
        p->matched = false;

        // Vicula o professor a escola
        e->match.push_back(p);
    }
}

// Faz a substituição de um professor da escola pelo professor atual
Professor *assign_Full(Professor *p, Escola *e)
{

    // Retorna o professor substituido
    Professor *retorno;

    // Anda pelos professores vinculados na escola
    for (int i = 0; (unsigned)i < e->match.size(); i++)
    {

        if (e->jobs_total == 2)
        {
            // Se a quantidade de habilidades do professor for diferente da preferencia da escola, então ele deve ser removido
            if (e->match[i]->hab != e->pref[0] || e->match[i]->hab != e->pref[1])
            {

                // Remove o vinculo do professor com a escola pois ele será substituido
                e->match[i]->match = NULL;

                // Muda para verdadeiro sua disponibilidade pois agora está sem escola
                e->match[i]->matched = true;

                // Atribui ao retorno o professor removido da escola pois deverá voltar para fila
                retorno = e->match[i];

                // Remove da lista de professores associados a escola
                e->match.erase(e->match.begin() + i);

                // Encerra a busca
                break;
            }
        }
        else
        {
            // Se a quantidade de habilidades do professor for diferente da preferencia da escola, então ele deve ser removido
            if (e->match[i]->hab != e->pref[0])
            {

                // Remove o vinculo do professor com a escola pois ele será substituido
                e->match[i]->match = NULL;

                // Muda para verdadeiro sua disponibilidade pois agora está sem escola
                e->match[i]->matched = true;

                // Atribui ao retorno o professor removido da escola pois deverá voltar para fila
                retorno = e->match[i];

                // Remove da lista de professores associados a escola
                e->match.erase(e->match.begin() + i);

                // Encerra a busca
                break;
            }
        }
    }

    // Vinculando novo professor na vaga que foi liberada
    assign_Free(p, e);

    // Retorna o professor removido
    return retorno;
}

// Verifica se um dos professores da escola pode ser removido para a substituição
bool change(int hab, Escola *e)
{

    bool podeRemover = false;
    if (e->jobs_total == 2)
    {

        // Se o professor que deseja aplicar a escola possui a quantidade de habilidade diferente da pretendida pela escola, então a escola recusa ele
        if (hab != e->pref[0])
        {
            if (hab != e->pref[1])
            {

                return false;
            }
        }

        // Avalia se a escola já está satisfeita com os professores que tem, caso não esteja, avalia se o professor ofertado é melhor que o professor que já possui
        if (e->match[0]->hab != e->pref[0])
        {
            if (hab == e->pref[0])
            {
                podeRemover = true;
            }
        }

        if (e->match[1]->hab != e->pref[1])
        {
            if (hab == e->pref[1])
            {
                podeRemover = true;
            }
        }
    }
    else
    {
        // Se o professor que deseja aplicar a escola possui a quantidade de habilidade diferente da pretendida pela escola, então a escola recusa ele
        if (hab != e->pref[0])
            return false;

        // Anda pelos professores vinculados a escola
        for (auto p : e->match)
        {

            // Se a quantidade de habilidade do professor da escola for diferente da pretentida, então ele pode ser removido
            if (p->hab != e->pref[0])
                return true;
        }
    }
    // Retorna falso caso todos atendem as preferencias da escola

    return podeRemover;
}

void emparelhamento_estavel_para_professor()
{

    // Fila de professores livres
    queue<Professor *> q;

    // Caminha pelos professores
    for (auto x : prof)
    {

        // Se o professor está livre, então ele entra na fila
        if (x->free())
            q.push(x);
    }

    // Enquanto a fila não está vazia
    while (!q.empty())
    {

        // Pega o professor da fila
        Professor *profe = q.front();
        q.pop();

        // Anda pelas escolas de sua preferência, do maior para o menor
        for (auto y : profe->pref)
        {

            // Pega a escola na ordem
            Escola *escol = esc[y - 1];

            // Se a escola está livre, então vincula o professor
            if (escol->free())
            {

                // Vincula o professor a uma escola com vaga
                assign_Free(profe, escol);

                // Encerra o processo de aplicação
                break;
            }

            // Se a escola está cheia, porém é possivel substituir um professor
            else if (!escol->free() and change(profe->hab, escol))
            {

                // Devolve o professor removido para a fila
                q.push(assign_Full(profe, escol));

                // Encerra o processo de aplicação
                break;
            }
        }
    }

    // Preenche as escolas que não conseguiram nenhum professor
    queue<Professor *> profLivre;
    for (auto x : prof)
    {
        if (x->free())
            profLivre.push(x);
    }
    if (profLivre.size() > 0)
    {
        for (auto y : esc)
        {
            while (y->free())
            {
                assign_Free(profLivre.front(), y);
                profLivre.pop();
            }
        }
    }
}

void print_escolas()
{

    for (auto x : esc)
    {

        printf("A escola %d cuja as habilidades esperadas eram:", x->code);
        for (size_t i = 0; i < (unsigned)x->jobs_total; i++)
        {
            printf("%d ", x->pref[i]);
        }
        printf("e ficou com os professores: ");
        int print = 0;
        for (auto y : x->match)
            if (x->match.size() > 1)
            {
                if (print < 1)
                {
                    printf("%d com habilidade %d e ", y->code, y->hab);
                    print = print + 1;
                }
                else
                {
                    printf("%d com habilidade %d", y->code, y->hab);
                    print = 0;
                }
            }
            else
            {
                printf("%d com habilidade %d", y->code, y->hab);
            }

        puts("");
    }
}

int main()
{

    read("entradaProj3TAG.txt");

    emparelhamento_estavel_para_professor();

    print_escolas();

    return 0;
}