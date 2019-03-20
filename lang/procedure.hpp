#ifndef PROCEDURE_H_
#define PROCEDURE_H_
#include "args.hpp"
#include "ast_node.hpp"
#include <string>
#include <vector>
#include <unordered_map>


class Procedure {

    public:

        Procedure();
        Procedure(const char *name, unsigned int arity, Args (*fun)(Args));
        Procedure(
            const char *name, unsigned int arity, 
            std::vector<AstNode> params, std::vector<AstNode> body
        );
        Args call(Args a);
        const char *get_name() const;
        unsigned int get_arity() const;
        bool is_native() const;

        bool operator==(const Procedure& other) const;
        bool operator!=(const Procedure& other) const;


    private:
        std::string name;
        unsigned int arity;
        Args (*callable)(Args);
        std::vector<AstNode> params;
        std::vector<AstNode> body;
        std::unordered_map<AstNode, AstNode, NodeHasher> bound_arguments;

        void bind(Args a);
        void substitute_bound_arguments(std::vector<AstNode> nodes_lst);

};

#endif
