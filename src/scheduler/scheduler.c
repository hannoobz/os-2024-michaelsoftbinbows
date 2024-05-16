#include "../header/scheduler/scheduler.h"

/* --- Scheduler --- */
/**
 * Initialize scheduler before executing init process 
 */
void scheduler_init(void) {
    // activate_timer_interrupt();
}

/**
 * Save context to current running process
 * 
 * @param ctx Context to save to current running process control block
 */
void scheduler_save_context_to_current_running_pcb(struct Context ctx) {
    for (int i=0; i<PROCESS_COUNT_MAX; i++) {
        if (_process_list[i].metadata.state == Ready) {
            _process_list[i].context = ctx;
        }
        break;
    }
}

/**
 * Trigger the scheduler algorithm and context switch to new process
 */
__attribute__((noreturn)) void scheduler_switch_to_next_process(void) {
    struct Context next_context;
    int context_id;
    for (int i=0; i<PROCESS_COUNT_MAX; i++) {
        if (_process_list[i].metadata.state == Ready) {
            scheduler_save_context_to_current_running_pcb(_process_list[i].context);
            if (i == PROCESS_COUNT_MAX - 1) {
                context_id = 0;
            } else {
                context_id = i+1;
            }
            _process_list[i].metadata.state = Waiting;
            break;
        }
    }
    _process_list[context_id].metadata.state = Running;
    //Virtual Address Space & Process Manipulation -- Change CR3 or smtn

    next_context = _process_list[context_id].context;
    // dummy variables
    // struct PageDirectory temp;
    // next_context.eip = 1; 
    // next_context.eflags = 2; 
    // next_context.page_directory_virtual_addr = &temp; 
    process_context_switch(next_context);
}
