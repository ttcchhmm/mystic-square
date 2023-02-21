/*
 * The goal of this file is to allow compiling the project while not every function is implemented.
 * This is achieved by printing a warning to the console when an unimplemented function is called.
 *
 * To use it, simply use the STUB macro in a header file after a function declaration but before the semicolon.
 *
 * Example:
 * void stubbedFunction(int anArgument) STUB;
 *
 * This file should be safe to delete and every reference to it removed at the end of the project.
 */

#ifndef MYSTICSQUARE_STUB_HH
#define MYSTICSQUARE_STUB_HH

#include <QDebug>

/**
 * Mark a stubbed function. Used to scaffold functions.
 */
#define STUB { qWarning() << "Stubbed."; }

#endif //MYSTICSQUARE_STUB_HH
