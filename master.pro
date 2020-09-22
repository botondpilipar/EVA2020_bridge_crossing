! include(common.pri)
TEMPLATE = subdirs


INCLUDEPATH += logic/include \
                access/include \
                utility/include \
                view/include \
                common/include

SUBDIRS += view \
            logic \
            access \
            test \

