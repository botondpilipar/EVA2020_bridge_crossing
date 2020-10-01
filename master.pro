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
            common \
            test \

RESOURCES = res.qrc

test.depends = logic
logic.depends = access
logic.depends = common
