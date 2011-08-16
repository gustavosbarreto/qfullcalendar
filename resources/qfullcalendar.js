var lastDropRevertFunc = null;
var lastResizeRevertFunc = null;

function undoDropEvent()
{
    lastDropRevertFunc();
}

function undoResizeEvent()
{
    lastResizeRevertFunc();
}

$(document).ready(function() {
    var date = new Date();
    var d = date.getDate();
    var m = date.getMonth();
    var y = date.getFullYear();

    $('#fullcalendar').fullCalendar({
        aspectRatio: 0,
        defaultView: QFullCalendar.defaultView(),
        editable: true,

        dayNames: QFullCalendar.dayNames(),
        dayNamesShort: QFullCalendar.dayNamesShort(),

        monthNames: QFullCalendar.monthNames(),
        monthNamesShort: QFullCalendar.monthNamesShort(),

        events: function(start, end, callback)
        {
            var events = [];
            var list = QFullCalendar.events(start.getTime() / 1000, end.getTime() / 1000);
            for (var i = 0; i < list.length; i++) {
                events.push(list[i]);
            }

            callback(events);
        },

        eventClick: function(calEvent, jsEvent, view) {
        },

        eventDrop: function(event, dayDelta, minuteDelta, allDay, revertFunc) {
            lastDropRevertFunc = revertFunc;
            QFullCalendar.emitEventDropped(event.id);
        },

        eventResize: function(event, dayDelta, minuteDelta, revertFunc) {
            lastResizeRevertFunc = revertFunc;
            QFullCalendar.emitEventResized(event.id);
        },

        select: function(start, end, allDay) {
//            QFullCalendar.showSelectHelperDialog();
        }
    });
});
