#include <cmath>
#include <cstdio>
#include <string>
#include "../turtle/turtle.hpp"
#include "../init/init_allegro.hpp"
#include "../init/init_turtle.hpp"
#include "../init/init_dispatch.hpp"
#include "../runtime/wrappers.hpp"
#include "../rendering/render_turtle.hpp"
#include "../lang/args.hpp"
#include "../lang/dispatch_table.hpp"
#include "../lang/procedure.hpp"
#include "../runtime/evaluator.hpp"
#include "../lang/tokenizer.hpp"
#include "../lang/ast_node.hpp"
#include "../lang/parser.hpp"




int main(int argc, char *argv[]) {

    init_allegro(800, 800, 60);

    init_turtle(400, 400, 0, true);
    init_dispatch_table();
    
    al_clear_to_color(al_map_rgb(255, 255, 255));
    render_turtle(__turtle__);
    al_flip_display();
    

    Tokenizer tok = Tokenizer();

    while (true) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        render_turtle(__turtle__);
        std::string input;
        std::getline(std::cin, input);
        std::cout << input << std::endl;
        tok.tokenize(input.c_str());

        AstNode root = parse_expression(tok);

        AstNode result = evaluate(root);

        std::cout << result << std::endl;
        al_flip_display();
    }
    

    al_rest(5);

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;

}
