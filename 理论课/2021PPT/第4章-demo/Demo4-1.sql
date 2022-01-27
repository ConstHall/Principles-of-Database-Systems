Use sysu;
delete from prereq;
delete from course;
insert into course values ('BIO-301', 'Genetics', 'Biology', '4');
insert into course values ('CS-190', 'Game Design', 'Comp. Sci.', '4');
insert into course values ('CS-315', 'Robotics', 'Comp. Sci.', '3');
insert into prereq values ('BIO-301', 'BIO-101');
insert into prereq values ('CS-190', 'CS-101');
insert into prereq values ('CS-347', 'CS-101');
