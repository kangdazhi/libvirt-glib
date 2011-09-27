/*
 * libvirt-gobject-config_domain.c: libvirt glib integration
 *
 * Copyright (C) 2008 Daniel P. Berrange
 * Copyright (C) 2010 Red Hat
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: Daniel P. Berrange <berrange@redhat.com>
 */

#include <config.h>

#include <string.h>

#include "libvirt-gconfig/libvirt-gconfig.h"

extern gboolean debugFlag;

#define DEBUG(fmt, ...) do { if (G_UNLIKELY(debugFlag)) g_debug(fmt, ## __VA_ARGS__); } while (0)

#define GVIR_CONFIG_DOMAIN_GET_PRIVATE(obj)                         \
        (G_TYPE_INSTANCE_GET_PRIVATE((obj), GVIR_TYPE_CONFIG_DOMAIN, GVirConfigDomainPrivate))

struct _GVirConfigDomainPrivate
{
    gboolean unused;
};

G_DEFINE_TYPE(GVirConfigDomain, gvir_config_domain, GVIR_TYPE_CONFIG_OBJECT);

enum {
    PROP_0,
    PROP_NAME,
};

static void gvir_config_domain_get_property(GObject *object,
                                            guint prop_id,
                                            GValue *value,
                                            GParamSpec *pspec)
{
    GVirConfigDomain *domain = GVIR_CONFIG_DOMAIN(object);

    switch (prop_id) {
    case PROP_NAME:
        g_value_take_string(value, gvir_config_domain_get_name(domain));
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    }
}


static void gvir_config_domain_class_init(GVirConfigDomainClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    g_type_class_add_private(klass, sizeof(GVirConfigDomainPrivate));

    object_class->get_property = gvir_config_domain_get_property;

    g_object_class_install_property(object_class,
                                    PROP_NAME,
                                    g_param_spec_string("name",
                                                        "Name",
                                                        "Domain Name",
                                                        NULL,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_STATIC_STRINGS));
}


static void gvir_config_domain_init(GVirConfigDomain *conn)
{
    GVirConfigDomainPrivate *priv;

    DEBUG("Init GVirConfigDomain=%p", conn);

    priv = conn->priv = GVIR_CONFIG_DOMAIN_GET_PRIVATE(conn);

    memset(priv, 0, sizeof(*priv));
}


GVirConfigDomain *gvir_config_domain_new(const gchar *xml)
{
    return GVIR_CONFIG_DOMAIN(g_object_new(GVIR_TYPE_CONFIG_DOMAIN,
                                           "doc", xml,
                                           "schema", DATADIR "/libvirt/schemas/domain.rng",
                                           NULL));
}

/* FIXME: do we add a GError ** to all getters in case there's an XML
 * parsing error? Doesn't work with gobject properties
 * => have a function to test if an error has occurred a la cairo?
 */
char *gvir_config_domain_get_name(GVirConfigDomain *domain)
{
    xmlNodePtr node;

    node = gvir_config_object_get_xml_node(GVIR_CONFIG_OBJECT(domain), NULL);
    if (node == NULL)
        return NULL;

    return gvir_config_xml_get_child_element_content_glib(node, "name");

}
