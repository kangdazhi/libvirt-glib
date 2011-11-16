/*
 * libvirt-gobject-domain-device.h: libvirt gobject integration
 *
 * Copyright (C) 2011 Red Hat
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
 * Author: Marc-André Lureau <marcandre.lureau@redhat.com>
 */

#if !defined(__LIBVIRT_GOBJECT_H__) && !defined(LIBVIRT_GOBJECT_BUILD)
#error "Only <libvirt-gobject/libvirt-gobject.h> can be included directly."
#endif

#ifndef __LIBVIRT_GOBJECT_DOMAIN_DEVICE_H__
#define __LIBVIRT_GOBJECT_DOMAIN_DEVICE_H__

G_BEGIN_DECLS

#define GVIR_TYPE_DOMAIN_DEVICE            (gvir_domain_device_get_type ())
#define GVIR_DOMAIN_DEVICE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GVIR_TYPE_DOMAIN_DEVICE, GVirDomainDevice))
#define GVIR_DOMAIN_DEVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GVIR_TYPE_DOMAIN_DEVICE, GVirDomainDeviceClass))
#define GVIR_IS_DOMAIN_DEVICE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GVIR_TYPE_DOMAIN_DEVICE))
#define GVIR_IS_DOMAIN_DEVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GVIR_TYPE_DOMAIN_DEVICE))
#define GVIR_DOMAIN_DEVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GVIR_TYPE_DOMAIN_DEVICE, GVirDomainDeviceClass))

typedef struct _GVirDomainDevice GVirDomainDevice;
typedef struct _GVirDomainDevicePrivate GVirDomainDevicePrivate;
typedef struct _GVirDomainDeviceClass GVirDomainDeviceClass;

struct _GVirDomainDevice
{
    GObject parent;

    GVirDomainDevicePrivate *priv;

    /* Do not add fields to this struct */
};

struct _GVirDomainDeviceClass
{
    GObjectClass parent_class;

    gpointer padding[20];
};


GType gvir_domain_device_get_type(void);

G_END_DECLS

#endif /* __LIBVIRT_GOBJECT_DOMAIN_DEVICE_H__ */