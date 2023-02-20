#ifndef MYSTICSQUARE_STUB_HH
#define MYSTICSQUARE_STUB_HH

#include <QDebug>

/**
 * Mark a stubbed function. Used to scaffold functions.
 */
#define STUB { qWarning() << "Stubbed."; }

#endif //MYSTICSQUARE_STUB_HH
